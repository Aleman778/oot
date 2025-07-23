#include "ultra64/ultratypes.h"
#include "batch.h"


void
flush_batch(Batch* batch) {
    if (batch->vertex_count > 0) {
        // opengl_submit_batch(batch);
    }
    
    batch->vertex_count = 0;
    batch->index_count = 0;

    batch->next_index = 0;
    batch->last_index = 0;
}


void
batch_check_space(Batch* batch, int size) {
    int new_size = batch->vertex_count + size;
    if (new_size > MAX_VERTEX_COUNT) {
        flush_batch(batch);
    }
}

void
push_vertex(Batch* batch, Vtx vertex) {
    Vertex v;
    v.x = vertex.v.ob[0];
    v.y = vertex.v.ob[1];
    v.z = vertex.v.ob[2];
    v.u = vertex.v.tc[0];
    v.v = vertex.v.tc[1];
    v.cr = vertex.v.cn[0];
    v.cg = vertex.v.cn[1];
    v.cb = vertex.v.cn[2];
    v.ca = vertex.v.cn[3];

    batch->vertices[batch->vertex_count++] = v;
}

void
push_triangle(Batch* batch, u16 v0, u16 v1, u16 v2) {
    batch->indices[batch->index_count++] = v0;
    batch->indices[batch->index_count++] = v1;
    batch->indices[batch->index_count++] = v2;
}

void
set_texture(Batch* batch, int texture0) {
    if (batch->texture0 != texture0) {
        flush_batch(batch);
        batch->texture0 = texture0;
    }
}
