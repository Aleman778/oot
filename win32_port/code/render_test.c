#include "global.h"
#include "opengl.h"
#include "matrix.h"
#include "batch.h"


GameStateOverlay* Graph_UpdateEntry(GameStateOverlay* nextOvl, GraphicsContext* gfxCtx);

u64
swap_u64(u64 val) {
    val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
    val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
    return (val << 32) | (val >> 32);
}

Batch batch;

void
render_batch(Batch* batch) {

    if (batch->vertex_count > 9 && batch->index_count > 0) {
        Mat4 projection_matrix = mat4_identity();
        if (batch->projection_matrix_count > 0) {
            projection_matrix = batch->projection_matrix_stack[batch->projection_matrix_count - 1];
        }
        Mat4 view_matrix = mat4_identity();
        if (batch->view_matrix_count > 0) {
            view_matrix = batch->view_matrix_stack[batch->view_matrix_count - 1];
        }
        
        // Mat4 mvp = mat4_mul(view_matrix, projection_matrix);
        Mat4 mvp = mat4_mul(mat4_transpose(mat4_perspective(90.0f, 480.0f/640.0f, -100.0f, 9999999.0f)), view_matrix);
            
        opengl.glBindBuffer(GL_ARRAY_BUFFER, opengl.vertex_buffer);
        opengl.glBufferSubData(GL_ARRAY_BUFFER, 0, batch->vertex_count*sizeof(Vertex), batch->vertices);
        
        opengl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, opengl.index_buffer);
        opengl.glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, batch->index_count*sizeof(u16), batch->indices);
        
        opengl.glUseProgram(opengl.default_shader.handle);

        // opengl.glActiveTexture(GL_TEXTURE0);
        // opengl.glBindTexture(GL_TEXTURE_2D, nintendo_rogo_tex.handle);
        int samplers[] = { 0 };
        opengl.glUniform1iv(opengl.default_shader.uniforms[SHADER_UNIFORM_TEXTURE0], 1, samplers);

        opengl.glUniformMatrix4fv(opengl.default_shader.uniforms[SHADER_UNIFORM_MVP], 1, GL_FALSE, mvp.data);
        
        opengl.glDrawElements(GL_TRIANGLES, batch->index_count, GL_UNSIGNED_SHORT, 0);
    }

    flush_batch(batch);
}

void
submit_draw_list(Batch* batch, Gfx* draw_list) {
    if (!draw_list) return;

    for (;;) {
        Gfx gfx = *draw_list++;
        // printf("%d: %llx\n", draw_list_count - 1, gfx.force_structure_alignment);

        int opcode = _SHIFTR(gfx.words.w0, 24, 8);
        if (opcode == G_ENDDL) break;

        switch (opcode) {
            case G_RDPPIPESYNC: {
                render_batch(batch);
            } break;

            case G_DL: {
                Gfx* other_draw_list = (Gfx*) ((u8*) (0x100000000) + gfx.words.w1); // TODO: Hack this will not be valid for all users
                submit_draw_list(batch, other_draw_list);

            } break;

            case G_MTX: {
                // G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW
                int flags = _SHIFTR(gfx.words.w0, 0, 8);
                Mtx* mtx = (Mtx*) ((u8*) (0x100000000) + gfx.words.w1); // TODO: Hack this will not be valid for all users
                
                Mat4 matrix;
                MtxF mtxf;
                Matrix_MtxToMtxF(mtx, &mtxf);
                for (int i = 0; i < 4; i++) { 
                    for (int j = 0; j < 4; j++) { 
                        matrix.data[i + j*4] = mtxf.mf[i][j];
                    }
                }

                Mat4* matrix_stack;
                int matrix_count;
                if (flags & G_MTX_PROJECTION) {
                    matrix_stack = batch->projection_matrix_stack;
                    matrix_count = batch->projection_matrix_count;
                } else {
                    matrix_stack = batch->view_matrix_stack;
                    matrix_count = batch->view_matrix_count;
                }

                Mat4 top_matrix;
                if (flags & G_MTX_LOAD) {
                    top_matrix = matrix;
                                        
                    if (flags & G_MTX_PUSH) {
                        matrix_stack[matrix_count++] = matrix;
                    }

                } else {
                    assert(matrix_count);
                    top_matrix = matrix_stack[matrix_count - 1];

                                        
                    if (flags & G_MTX_PUSH) {
                        matrix_stack[matrix_count++] = matrix;
                    }

                    // if (matrix_count > 0) {
                    // } else {
                        // top_matrix = mat4_identity();
                    // }
                    top_matrix = mat4_mul(top_matrix, matrix);
                }

                assert(matrix_count);
                matrix_stack[matrix_count - 1] = top_matrix;
                // if (matrix_count == 0) {
                // } else {
                    // matrix_stack[0] = top_matrix;
                // }

                if (flags & G_MTX_PROJECTION) {
                    batch->projection_matrix_count = matrix_count;
                } else {
                    batch->view_matrix_count = matrix_count;
                }   
                // printf("%f, %f, %f, %f\n", matrix.data[0], matrix.data[1], matrix.data[2], matrix.data[3]);
            } break;

            case G_POPMTX: {
                assert(0);
            } break;

            case G_VTX: {
                batch->next_index = batch->last_index;

                int n = _SHIFTR(gfx.words.w0, 12, 8);
                int end = _SHIFTR(gfx.words.w0, 1, 7); // ??
                Vtx* vertices = (Vtx*) ((u8*) (0x100000000) + gfx.words.w1); // TODO: Hack this will not be valid for all users
                // Vtx* vertices = nintendo_rogo_staticVtx_001C00;

                for (int i = 0; i < n; i++) {
                    push_vertex(batch, vertices[i]);
                    batch->last_index++;
                }
                // printf("G_VTX: n = %d, end = %d, addr = %llx\n", n, end, vertices);
            } break;

            case G_TRI1: {
                int v0 = batch->next_index + _SHIFTR(gfx.words.w0,   16, 8) / 2;
                int v1 = batch->next_index + _SHIFTR(gfx.words.w0,    8, 8) / 2;
                int v2 = batch->next_index + _SHIFTR(gfx.words.w0,    0, 8) / 2;
                
                push_triangle(batch, v0, v1, v2);
                // printf("G_TRI1: v0 = %d, v1 = %d, v2 = %d\n", v0, v1, v2);
            } break;

            case G_TRI2: {
                int v0 = batch->next_index + _SHIFTR(gfx.words.w0,   16, 8) / 2;
                int v1 = batch->next_index + _SHIFTR(gfx.words.w0,    8, 8) / 2;
                int v2 = batch->next_index + _SHIFTR(gfx.words.w0,    0, 8) / 2;
                push_triangle(batch, v0, v1, v2);

                int v3 = batch->next_index + _SHIFTR(gfx.words.w1,   16, 8) / 2;
                int v4 = batch->next_index + _SHIFTR(gfx.words.w1,    8, 8) / 2;
                int v5 = batch->next_index + _SHIFTR(gfx.words.w1,    0, 8) / 2;
                push_triangle(batch, v3, v4, v5);

                // printf("G_TRI2: v0 = %d, v1 = %d, v2 = %d: v3 = %d, v4 = %d, v5 = %d\n", v0, v1, v2, v3, v4, v5);
            } break;
        }
    }
}

void
render_test(int w, int h) {
    opengl_clear_render_target(0.0f, 0.0f, 0.0f, 1.0f);

    #define WIDTH 192
    #define HEIGHT 32

    int width = WIDTH; int height = HEIGHT;
#if 0
    static Texture nintendo_rogo_tex;
    if (!nintendo_rogo_tex.handle) {
        nintendo_rogo_tex.width = width;
        nintendo_rogo_tex.height = height;
        nintendo_rogo_tex.channels = 4;
        u32 newdata[WIDTH*HEIGHT];


        // Big endian to little
        u8 neworigin_data[WIDTH*HEIGHT];
        u64* neworigin = (u64*) neworigin_data;
        for (int y = 0; y < WIDTH*HEIGHT/8; y++) {
            neworigin[y] = swap_u64(nintendo_rogo_static_Tex_000000[y]);
        }

        u8* origdata = (u8*) neworigin;
        
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                
                int new_pos = ((height - y - 1) * width) + x;
                int pos = (y * width) + x;
                u8 byte = origdata[pos];
                u8* bytes = (u8*) (newdata + new_pos);
                bytes[0] = byte;
                bytes[1] = byte;
                bytes[2] = byte;
                bytes[3] = 255;
            }
        }

        Texture_Params params;
        bzero(&params, sizeof(Texture_Params));
        opengl_init_texture(&nintendo_rogo_tex, (u8*) newdata, GL_RGBA, GL_RGBA, params);
    }
#endif

    static GraphicsContext gfxCtx;

    static bool is_initialized = false;
    if (!is_initialized) {
        is_initialized = true;
        PRINTF(T("グラフィックスレッド実行開始\n", "Start graphic thread execution\n"));
        Graph_Init(&gfxCtx);
    }

    static GameStateOverlay* nextOvl = &gGameStateOverlayTable[GAMESTATE_SETUP];
    nextOvl = Graph_UpdateEntry(nextOvl, &gfxCtx);


    // Render graphics
    Gfx* draw_list = gfxCtx.polyOpaBuffer;    
    flush_batch(&batch);
    batch.projection_matrix_count = 0;
    batch.view_matrix_count = 0;

    opengl.glViewport(0, 0, w, h);
    submit_draw_list(&batch, draw_list);

    render_batch(&batch);
}