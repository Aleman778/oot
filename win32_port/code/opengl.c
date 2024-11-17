#include "opengl.h"
#include "assert.h"

#define pln(fmt, ...)

void
opengl_debug_callback(GLenum source,
                      GLenum type,
                      GLuint id,
                      GLenum severity,
                      GLsizei length,
                      const GLchar *message,
                      const void *userParam) {
    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
        printf("error: %.*s\n", (int) length, message);
        //assert(0);
    }
}

void
opengl_init_texture(Texture* texture, u8* image_data, GLenum internal_format, GLenum format, Texture_Params params) {
    opengl.glGenTextures(1, (GLuint*) &texture->handle);
    opengl.glBindTexture(GL_TEXTURE_2D, texture->handle);
    GLenum wrap_s = GL_REPEAT, wrap_t = GL_REPEAT;
    
    
    switch (params.filter) {
        case TEXTURE_FILTER_POINT: {
            assert(!params.mipmaps && "Point filter does not support mipmapping");
            opengl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            opengl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        } break;
        
        case TEXTURE_FILTER_BILINEAR: {
            if (params.mipmaps) {
                opengl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
                opengl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            } else {
                opengl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                opengl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
        } break;
        
        case TEXTURE_FILTER_TRILINEAR: {
            if (params.mipmaps) {
                opengl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                opengl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            } else {
                assert(0 && "Trilinear filtering requires mipmapping");
                opengl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                opengl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
        } break;
    }
    
    opengl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    opengl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    opengl.glTexImage2D(GL_TEXTURE_2D, 0, internal_format, texture->width, texture->height, 0,
                        format, GL_UNSIGNED_BYTE, image_data);
    
    if (params.mipmaps) {
        opengl.glGenerateMipmap(GL_TEXTURE_2D);
    }
}

// inline void
// renderer_init_texture(Texture* texture, u8* image_data, Texture_Params params) {
//     opengl_init_texture(texture, image_data, texture->channels > 3 ? GL_RGBA : GL_RGB, GL_RGBA, params);
// }

// Render_Texture
// opengl_load_render_texture(int width, int height) {
//     Render_Texture result = {};
    
//     result.texture.width = width;
//     result.texture.height = height;
//     result.texture.channels = 4;
//     opengl_init_texture(&result.texture, 0, GL_RGBA);
    
    
//     result.depth_texture.width = width;
//     result.depth_texture.height = height;
//     result.depth_texture.channels = 1;
//     opengl_init_texture(&result.depth_texture, 0, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT);
    
//     opengl.glGenFramebuffers(1, (GLuint*) &result.handle);
//     opengl.glBindFramebuffer(GL_FRAMEBUFFER, result.handle);
//     opengl.glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, result.texture.handle, 0);
//     opengl.glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, result.depth_texture.handle , 0);
//     GLenum status = opengl.glCheckFramebufferStatus(GL_FRAMEBUFFER);
//     assert(status == GL_FRAMEBUFFER_COMPLETE && "failed to create framebuffer!");
//     opengl.glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
//     return result;
// }

inline bool
check_shader(GLuint shader, const GLchar* name) {
    GLint success;
    opengl.glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLsizei message_count = 0;
        const GLchar* message = (const GLchar*) malloc(1024);
        opengl.glGetShaderInfoLog(shader, 1024, (GLsizei*) &message_count, (GLchar*) message);
        pln("%s: %.*s\n", name, message_count, message);
        free((void*) message);
        return false;
    }
    
    return true;
}

bool
check_program(GLuint program, const GLchar* name) {
    GLint success;
    opengl.glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLsizei message_count = 0;
        const GLchar* message = (const GLchar*) malloc(1024);
        opengl.glGetProgramInfoLog(program, 1024, &message_count, (GLchar*) message);
        pln("%s: %.*s", name, message_count, message);
        free((void*) message);
        return false;
    }
    
    return true;
}

#if defined(__clang__)
#define glsl_shader_header \
"#version 300 es\n" \
"precision highp float;\n" \
"precision lowp sampler2D;\n" \
"precision highp int;\n"
#else
#define glsl_shader_header \
"#version 330\n"
#endif

static const GLchar* default_vertex_source_glsl =
""
glsl_shader_header
"layout (location = 0) in vec2 in_position;\n"
"layout (location = 1) in vec2 in_texcoord;\n"
"layout (location = 2) in vec4 in_color;\n"
"uniform mat4 u_mvp;\n"
"out vec2 v_texcoord;\n"
"out vec4 v_color;\n"
"void main() {\n"
"  gl_Position = u_mvp * vec4(in_position, 0.0f, 1.0f);\n"
"  v_texcoord = in_texcoord;\n"
"  v_color = in_color;\n"
"}\n";


static const GLchar* default_fragment_source_glsl =
glsl_shader_header
"in vec2 v_texcoord;\n"
"in vec4 v_color;\n"
"uniform sampler2D u_texture0;\n"
"out vec4 frag_color;\n"
"void main() {\n"
"    frag_color = texture(u_texture0, v_texcoord) * v_color;\n"
"}\n";

static const GLchar* sdf_text_fragment_source_glsl =
glsl_shader_header
"in vec2 v_texcoord;\n"
"in vec4 v_color;\n"
"uniform sampler2D u_texture0;\n"
"out vec4 frag_color;\n"
"void main() {\n"
"    float d = texture(u_texture0, v_texcoord).a;\n"
"    float aaf = fwidth(d);\n"
"    frag_color = vec4(v_color.xyz, v_color.a * smoothstep(0.5f - aaf, 0.5f + aaf, d));\n"
"}\n";


Shader
opengl_compile_shader_from_source(const GLchar* vertex_filename, const GLchar* vertex_source,
                                  const GLchar* fragment_filename, const GLchar* fragment_source) {
    GLuint program = opengl.glCreateProgram();
    GLuint vertex_shader = opengl.glCreateShader(GL_VERTEX_SHADER);
    opengl.glShaderSource(vertex_shader, 1, &vertex_source, 0);
    opengl.glCompileShader(vertex_shader);
    check_shader(vertex_shader, vertex_filename);
    opengl.glAttachShader(program, vertex_shader);
    
    GLuint fragment_shader = opengl.glCreateShader(GL_FRAGMENT_SHADER);
    opengl.glShaderSource(fragment_shader, 1, &fragment_source, 0);
    opengl.glCompileShader(fragment_shader);
    check_shader(fragment_shader, fragment_filename);
    opengl.glAttachShader(program, fragment_shader);
    
    opengl.glLinkProgram(program);
    opengl.glDeleteShader(vertex_shader);
    opengl.glDeleteShader(fragment_shader);
    check_program(program, "Shader");
    
    Shader result;
    bzero(&result, sizeof(Shader));
    result.uniforms[SHADER_UNIFORM_MVP] = opengl.glGetUniformLocation(program, "u_mvp");
    result.uniforms[SHADER_UNIFORM_TEXTURE0] = opengl.glGetUniformLocation(program, "u_texture0");
    result.handle = program;
    return result;
}

void
init_opengl() {
#if BUILD_INTERNAL
    opengl.glEnable(GL_DEBUG_OUTPUT);
    opengl.glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
    opengl.glDebugMessageCallback(opengl_debug_callback, 0);
    opengl.glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif
    
    opengl.glGenVertexArrays(1, &opengl.vertex_array);
    opengl.glBindVertexArray(opengl.vertex_array);
    
    opengl.glGenBuffers(1, &opengl.vertex_buffer);
    opengl.glBindBuffer(GL_ARRAY_BUFFER, opengl.vertex_buffer);
    opengl.glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*1000, 0, GL_DYNAMIC_DRAW);
    
    opengl.glEnableVertexAttribArray(0);
    opengl.glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    
    opengl.glEnableVertexAttribArray(1);
    opengl.glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (2 * sizeof(f32)));
    
    opengl.glEnableVertexAttribArray(2);
    opengl.glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (4 * sizeof(f32)));
    
    opengl.glGenBuffers(1, &opengl.index_buffer);
    opengl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, opengl.index_buffer);
    opengl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u16)*1500, 0, GL_DYNAMIC_DRAW);
    
    // Create empty white texture
    u32 empty = 0xFFFFFFFF;
    Texture empty_texture;
    empty_texture.width = 1;
    empty_texture.height = 1;
    empty_texture.channels = 1;
    Texture_Params params;
    bzero(&params, sizeof(Texture_Params));
    opengl_init_texture(&empty_texture, (u8*) &empty, GL_RGBA, GL_RGBA, params);
    opengl.default_texture = empty_texture.handle;
    
    opengl.glEnable(GL_BLEND);
    opengl.glEnable(GL_SCISSOR_TEST);
    
    // Compile shaders
    opengl.default_shader = opengl_compile_shader_from_source("default_vertex_shader", default_vertex_source_glsl,
                                                              "default_fragment_shader", default_fragment_source_glsl);
    opengl.sdf_shader = opengl_compile_shader_from_source("default_vertex_shader", default_vertex_source_glsl,
                                                          "sdf_text_fragment_shader", sdf_text_fragment_source_glsl);
}

// void
// opengl_set_render_target(Render_Texture framebuffer) {
//     opengl.glBindFramebuffer(GL_FRAMEBUFFER, (framebuffer.handle > 0) ? framebuffer.handle : 0);
//     opengl.glViewport(0, 0, (int) acorn.render_size.width, (int) acorn.render_size.height);
// }

#if 0
void
opengl_end_drawing(OpenGL_Context* opengl) {
    opengl.glViewport(0, 0, (int) acorn.screen_size.width, (int) acorn.screen_size.height);
    opengl.glBindFramebuffer(GL_FRAMEBUFFER, 0);
    opengl.glBindFramebuffer(GL_READ_FRAMEBUFFER, opengl.main_framebuffer);
    opengl.glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    opengl.glBlitFramebuffer(0, 0, 
                             opengl.main_color_texture.width, opengl.main_color_texture.height,
                             0, 0,
                             (int) acorn.screen_size.width, (int) acorn.screen_size.height,
                             GL_COLOR_BUFFER_BIT, GL_NEAREST);
}
#endif

void
opengl_submit_batch(Batch* batch) {
    // f32 render_height = get_render_size().height;
    // opengl.glScissor((int) batch->clip_rectangle.x, (int) (render_height - (batch->clip_rectangle.y + batch->clip_rectangle.height)),
    //                  (int) batch->clip_rectangle.width, (int) batch->clip_rectangle.height);
    
    // if (batch->vertex_count > 0) {
    //     opengl.glBindBuffer(GL_ARRAY_BUFFER, opengl.vertex_buffer);
    //     opengl.glBufferSubData(GL_ARRAY_BUFFER, 0, batch->vertex_count*sizeof(Vertex), batch->vertices);
    // }
    
    // if (batch->index_count > 0) {
    //     opengl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, opengl.index_buffer);
    //     opengl.glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, batch->index_count*sizeof(u16), batch->indices);
    // }
    
    // opengl.glUseProgram(batch->shader.handle ? batch->shader.handle : opengl.default_shader.handle);
    // opengl.glUniformMatrix4fv(batch->shader.uniforms[SHADER_UNIFORM_MVP], 1, GL_TRUE, batch->view_projection_matrix.data);
    
    // // Setup textures
    // int samplers[] = { 0 };
    // opengl.glActiveTexture(GL_TEXTURE0);
    // opengl.glBindTexture(GL_TEXTURE_2D, batch->texture0 ? batch->texture0 : opengl.default_texture);
    // opengl.glUniform1iv(batch->shader.uniforms[SHADER_UNIFORM_TEXTURE0], 1, samplers);
    // TODO(Alexander): add support for multiple simultaneus textures
#if 0
    // Bind textures to slots
    int texture_slots[32];
    opengl.glActiveTexture(GL_TEXTURE0);
    opengl.glBindTexture(GL_TEXTURE_2D, opengl.default_texture);
    texture_slots[0] = 0;
    for (int texture_index = 1; texture_index < batch->texture_count; texture_index++) {
        opengl.glActiveTexture(GL_TEXTURE0 + texture_index);
        opengl.glBindTexture(GL_TEXTURE_2D, (GLuint) batch->textures[texture_index]);
        texture_slots[texture_index] = texture_index;
    }
    opengl.glUniform1iv(batch->shader.uniforms[1], batch->texture_count > 0 ? batch->texture_count : 1, texture_slots); 
#endif
    
    
    // if (batch->mode == DRAW_TRIANGLES && batch->index_count > 0) {
    //     opengl.glDrawElements(GL_TRIANGLES, batch->index_count, GL_UNSIGNED_SHORT, 0);
        
    // } else if (batch->mode == DRAW_LINES && batch->vertex_count > 0) {
    //     opengl.glDrawArrays(GL_LINES, 0, batch->vertex_count);
    // }
}

inline void
opengl_clear_render_target(f32 red, f32 green, f32 blue, f32 alpha) {
    opengl.glDisable(GL_SCISSOR_TEST);
    opengl.glClearColor(red, green, blue, alpha);
    opengl.glClear(GL_COLOR_BUFFER_BIT);
    opengl.glEnable(GL_SCISSOR_TEST);
}
