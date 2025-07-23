#ifndef _BATCH
#define _BATCH

#include "global.h"
#include "matrix.h"

typedef enum Draw_Mode {
    DRAW_LINES,
    DRAW_TRIANGLES,
} Draw_Mode;

typedef struct Vertex {
    f32 x, y, z;
    f32 u, v;
    f32 cr, cg, cb, ca;
} Vertex;

typedef struct Batch {
    Draw_Mode mode;
    
    int texture0;

    int next_index;
    int last_index;
    
    #define MAX_VERTEX_COUNT 1000
    Vertex vertices[MAX_VERTEX_COUNT];
    int vertex_count;
    
    #define MAX_INDEX_COUNT 1000
    u16 indices[MAX_INDEX_COUNT];
    int index_count;
    
    Mat4 view_matrix_stack[4];
    int view_matrix_count;
    Mat4 projection_matrix_stack[4];
    int projection_matrix_count;
    
    Mat4 view_projection_matrix;
} Batch;

void
flush_batch(Batch* batch);

void
batch_check_space(Batch* batch, int size);

void
push_vertex(Batch* batch, Vtx vertex);

void
push_triangle(Batch* batch, u16 v0, u16 v1, u16 v2);

void
set_texture(Batch* batch, int texture0);

#endif