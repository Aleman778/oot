#include "ultra64/ultratypes.h"
#include "stdbool.h"

// OpenGL constants
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000

#define GL_FALSE                          0
#define GL_TRUE                           1

#define GL_DEBUG_OUTPUT                37600
#define GL_DEBUG_OUTPUT_SYNCHRONOUS    33346
#define GL_DEBUG_SEVERITY_NOTIFICATION 33387

#define GL_DONT_CARE 4352

#define GL_POINT                          0x1B00
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02

#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_QUADS                          0x0007

#define GL_TEXTURE_1D                     0x0DE0
#define GL_TEXTURE_2D                     0x0DE1
#define GL_DEPTH_COMPONENT                0x1902
#define GL_RED                            0x1903
#define GL_GREEN                          0x1904
#define GL_BLUE                           0x1905
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
#define GL_REPEAT                         0x2901
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF

#define GL_FRAMEBUFFER                    0x8D40
#define GL_READ_FRAMEBUFFER               0x8CA8
#define GL_DRAW_FRAMEBUFFER               0x8CA9
#define GL_MAX_COLOR_ATTACHMENTS          0x8CDF
#define GL_COLOR_ATTACHMENT0              0x8CE0
#define GL_DEPTH_ATTACHMENT               0x8D00
#define GL_STENCIL_ATTACHMENT             0x8D20
#define GL_FRAMEBUFFER_COMPLETE           0x8CD5

#define GL_SCISSOR_TEST                   0x0C11

#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
#define GL_BLEND                          0x0BE2
#define GL_FUNC_ADD                       0x8006
#define GL_FUNC_REVERSE_SUBTRACT          0x800B
#define GL_FUNC_SUBTRACT                  0x800A
#define GL_MIN                            0x8007
#define GL_MAX                            0x8008
#define GL_NONE                           0
#define GL_FRONT_LEFT                     0x0400
#define GL_FRONT_RIGHT                    0x0401
#define GL_BACK_LEFT                      0x0402
#define GL_BACK_RIGHT                     0x0403
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_LEFT                           0x0406
#define GL_RIGHT                          0x0407
#define GL_FRONT_AND_BACK                 0x0408
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_OUT_OF_MEMORY                  0x0505
#define GL_CW                             0x0900
#define GL_CCW                            0x0901
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893

#define GL_LINK_STATUS                    0x8B82
#define GL_COMPILE_STATUS                 0x8B81
#define GL_INFO_LOG_LENGTH                0x8B84

#define GL_READ_ONLY                      0x88B8
#define GL_WRITE_ONLY                     0x88B9
#define GL_READ_WRITE                     0x88BA
#define GL_BUFFER_ACCESS                  0x88BB
#define GL_BUFFER_MAPPED                  0x88BC
#define GL_BUFFER_MAP_POINTER             0x88BD
#define GL_STREAM_DRAW                    0x88E0
#define GL_STREAM_READ                    0x88E1
#define GL_STREAM_COPY                    0x88E2
#define GL_STATIC_DRAW                    0x88E4
#define GL_STATIC_READ                    0x88E5
#define GL_STATIC_COPY                    0x88E6
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_DYNAMIC_READ                   0x88E9
#define GL_DYNAMIC_COPY                   0x88EA

#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406

// OpenGL definitions
typedef void GLvoid;
typedef u32 GLenum;
typedef f32 GLfloat;
typedef s32 GLint;
typedef s32 GLsizei;
typedef u32 GLbitfield;
typedef f64 GLdouble;
typedef u32 GLuint;
typedef u8 GLboolean;
typedef u8 GLubyte;
typedef f32 GLclampf;
typedef f64 GLclampd;
typedef s64 GLsizeiptr;
typedef s64 GLintptr;
typedef char GLchar;
typedef s16 GLshort;
typedef s8 GLbyte;
typedef u16 GLushort;
typedef u16 GLhalf;
//typedef struct __GLsync* GLsync;
typedef void* GLsync;
typedef u64 GLuint64;
typedef s64 GLint64;

typedef void type_glDisable (GLenum cap);
typedef void type_glEnable (GLenum cap);
typedef void type_glClear (GLbitfield mask);
typedef void type_glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
typedef void type_glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void type_glBlendFunc (GLenum sfactor, GLenum dfactor);
typedef void type_glBlendEquation (GLenum mode);
typedef void type_glScissor (GLint x, GLint y, GLsizei width, GLsizei height);

typedef void type_glGenBuffers(GLsizei n, GLuint* buffers);
typedef void type_glBindBuffer(GLenum target, GLuint buffer);
typedef void type_glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void type_glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
typedef void type_glGenVertexArrays (GLsizei n, GLuint *arrays);
typedef void type_glBindVertexArray (GLuint array);
typedef void type_glVertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
typedef void type_glEnableVertexAttribArray (GLuint index);
typedef GLint type_glGetAttribLocation (GLuint program, const GLchar* name);
typedef void type_glDrawArrays (GLenum mode, GLint first, GLsizei count);
typedef void type_glDrawElements (GLenum mode, GLsizei count, GLenum type, const void *indices);

typedef void type_glGenTextures (GLsizei n, GLuint *textures);
typedef void type_glBindTexture (GLenum target, GLuint texture);
typedef void type_glTexParameteri (GLenum target, GLenum pname, GLint param);
typedef void type_glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void type_glActiveTexture (GLenum texture);
typedef void type_glGenerateMipmap (GLenum texture);

typedef void type_glBindFramebuffer (GLenum target, GLuint framebuffer);
typedef void type_glDeleteFramebuffers (GLsizei n, const GLuint *framebuffers);
typedef void type_glGenFramebuffers (GLsizei n, GLuint *framebuffers);
typedef GLenum type_glCheckFramebufferStatus (GLenum target);
typedef void type_glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);

typedef void type_glCompileShader (GLuint shader);
typedef GLuint type_glCreateProgram (void);
typedef GLuint type_glCreateShader (GLenum type);
typedef void type_glDeleteProgram (GLuint program);
typedef void type_glDeleteShader (GLuint shader);
typedef void type_glAttachShader (GLuint program, GLuint shader);
typedef void type_glDetachShader (GLuint program, GLuint shader);
typedef void type_glLinkProgram (GLuint program);
typedef void type_glShaderSource (GLuint shader, GLsizei count, const GLchar** string, const GLint *length);
typedef void type_glUseProgram (GLuint program);
typedef void type_glGetProgramiv (GLuint program, GLenum pname, GLint *params);
typedef void type_glGetProgramInfoLog (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void type_glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
typedef void type_glGetShaderInfoLog (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void type_glGetProgramiv (GLuint program, GLenum pname, GLint *params);
typedef void type_glGetProgramInfoLog (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef GLint type_glGetUniformLocation (GLuint program, const GLchar* name);
typedef void type_glUniform1iv (GLint location, GLsizei count, const GLint *value);
typedef void type_glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

// Debug OpenGL
typedef void (*DEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
typedef void type_glDebugMessageCallback(DEBUGPROC callback, void * userParam);
typedef void type_glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);

#define SHADER_UNIFORM_MVP 0
#define SHADER_UNIFORM_TEXTURE0 1
#define SHADER_UNIFORM_COUNT 2

typedef struct Shader {
    int handle;
    int uniforms[SHADER_UNIFORM_COUNT];
} Shader;


typedef struct OpenGL_Context {
    GLuint vertex_array;
    GLuint vertex_buffer;
    GLuint index_buffer;
    GLuint default_texture;
    
    Shader default_shader;
    Shader sdf_shader;
    
#define OPENGL_FUNC(name) type_##name* name
    OPENGL_FUNC(glEnable);
    OPENGL_FUNC(glDisable);
    OPENGL_FUNC(glViewport);
    OPENGL_FUNC(glClear);
    OPENGL_FUNC(glClearColor);
    OPENGL_FUNC(glBlendFunc);
    OPENGL_FUNC(glScissor);
    OPENGL_FUNC(glBlendEquation);
    OPENGL_FUNC(glGenBuffers);
    OPENGL_FUNC(glBindBuffer);
    OPENGL_FUNC(glBufferData);
    OPENGL_FUNC(glBufferSubData);
    OPENGL_FUNC(glGenVertexArrays);
    OPENGL_FUNC(glBindVertexArray);
    OPENGL_FUNC(glVertexAttribPointer);
    OPENGL_FUNC(glEnableVertexAttribArray);
    OPENGL_FUNC(glDrawArrays);
    OPENGL_FUNC(glDrawElements);
    OPENGL_FUNC(glGenTextures);
    OPENGL_FUNC(glBindTexture);
    OPENGL_FUNC(glTexParameteri);
    OPENGL_FUNC(glTexImage2D);
    OPENGL_FUNC(glActiveTexture);
    OPENGL_FUNC(glGenerateMipmap);
    OPENGL_FUNC(glBindFramebuffer);
    OPENGL_FUNC(glDeleteFramebuffers);
    OPENGL_FUNC(glGenFramebuffers);
    OPENGL_FUNC(glCheckFramebufferStatus);
    OPENGL_FUNC(glFramebufferTexture2D);
    OPENGL_FUNC(glCreateShader);
    OPENGL_FUNC(glDeleteShader);
    OPENGL_FUNC(glShaderSource);
    OPENGL_FUNC(glCompileShader);
    OPENGL_FUNC(glAttachShader);
    OPENGL_FUNC(glGetShaderiv);
    OPENGL_FUNC(glGetShaderInfoLog);
    OPENGL_FUNC(glGetProgramiv);
    OPENGL_FUNC(glGetProgramInfoLog);
    OPENGL_FUNC(glCreateProgram);
    OPENGL_FUNC(glLinkProgram);
    OPENGL_FUNC(glUseProgram);
    OPENGL_FUNC(glGetUniformLocation);
    OPENGL_FUNC(glUniform1iv);
    OPENGL_FUNC(glUniformMatrix4fv);
    OPENGL_FUNC(glDebugMessageCallback);
    OPENGL_FUNC(glDebugMessageControl);
} OpenGL_Context;

static OpenGL_Context opengl;

typedef struct Vertex {
    f32 x, y, z;
} Vertex;

typedef struct Batch {
    int unused;
} Batch;

typedef struct Texture {
    int handle;
    int width;
    int height;
    int channels;
} Texture;

typedef enum Texture_Filter {
    TEXTURE_FILTER_POINT = 0,
    TEXTURE_FILTER_BILINEAR = 1,
    TEXTURE_FILTER_TRILINEAR = 2,
} Texture_Filter;

typedef struct Texture_Params {
    Texture_Filter filter;
    bool mipmaps;
} Texture_Params;


void init_opengl();

void opengl_submit_batch(Batch* batch);

inline void opengl_clear_render_target(f32 red, f32 green, f32 blue, f32 alpha);