#include "ultra64/ultratypes.h"

#ifndef _MAT4
#define _MAT4

// Mat4, 4 by 4 matrix
typedef union Mat4 {
    struct {
        f32 m00, m01, m02, m03;
        f32 m10, m11, m12, m13;
        f32 m20, m21, m22, m23;
        f32 m30, m31, m32, m33;
    };
    f32 data[16];
} Mat4;

Mat4 mat4_identity();

Mat4 mat4_orthographic(f32 left, f32 top, f32 right, f32 bottom, f32 near, f32 far);

Mat4 mat4_perspective(f32 fov, f32 aspect_ratio, f32 near, f32 far);
    
Mat4 mat4_mul(Mat4 a, Mat4 b);

Mat4 mat4_transpose(Mat4 m);


#endif