#define STDINT_H

#include "windows.h"
#include "xinput.h"
#include "assert.h"

#undef NULL
#include "ultra64/ultratypes.h"
#include "libc/stdbool.h"

#include "opengl.h"

#define pln(fmt, ...)

// TODO: debug code
void MainTest(void* arg, void* heap_memory);
void render_test(int w, int h);

const char*
cstring_print(const char* format, ...) {
    return format;
    // va_list args;
    // va_start(args, format);
    
    // int buf_size = 256;
    // char* result = (char*) malloc(buf_size);
    // int count = vsnprintf(result, buf_size, format, args) + 1;
    
    // if (count >= buf_size) {
    //     char* new_result = (char*) realloc(result, count);
    //     if (!new_result) {
    //         free(result);
    //         new_result = (char*) malloc(count);
    //     }
    //     result = new_result;
    //     vsnprintf(result, count, format, args);
    // }
    
    // result[count - 1] = '\0';
    
    // va_end(args);
    // return result;
}

// TODO(Alexander): these are global for now
bool global_is_running = false;
bool sleep_is_granular = false;
f32 global_delta_time;
f64 target_seconds_per_frame;

// TODO(Alexander): this is global for now, maybe we want multiple windows in the future
HWND global_window;
HDC global_device_context;
bool global_fullscreen;


LRESULT CALLBACK
win32_main_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
    LRESULT result = 0;
    
    switch (message) {
        case WM_CLOSE:
        case WM_DESTROY: {
            global_is_running = false;
        } break;
        
        default: {
            result = DefWindowProcA(window, message, w_param, l_param);
        } break;
    }
    
    return result;
}

void
win32_fatal_error(const char* message) {
    MessageBoxA(global_window, message, "Fatal error occured", MB_OK);
    ExitProcess(1);
}

void
win32_warning(const char* message) {
    MessageBoxA(global_window, message, "Note", MB_OK);
}

void
win32_process_pending_messages() {
    MSG message;
    while (PeekMessageA(&message, 0, 0, 0, PM_REMOVE)) {
        switch (message.message) {
            case WM_QUIT: {
                global_is_running = false;
            } break;
            
            default: {
                TranslateMessage(&message);
                DispatchMessageA(&message);
            } break;
        }
    }    
}

#if 0
void
win32_process_keyboard_message(Input_Button_State* new_state, bool is_down) {
    if (new_state->ended_down != is_down) {
        new_state->num_half_transitions++;
        new_state->ended_down = is_down;
    }
}

void
win32_process_pending_messages(Input* input) {
    // Reset input
    for (int i = 0; i < KEY_COUNT; i++) {
        input->buttons[i] = { 0, input->buttons[i].ended_down };
    }
    input->mouse_wheel_delta = vec2_zero;
    
    MSG message;
    while (PeekMessageA(&message, 0, 0, 0, PM_REMOVE)) {
        switch (message.message) {
            case WM_QUIT: {
                global_is_running = false;
            } break;
            
            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP:
            case WM_KEYDOWN:
            case WM_KEYUP: {
                // TODO(alexander): improve the keyboard handling system
                u32 vkcode = (u32) message.wParam;
                bool was_down = (message.lParam & (1 << 30)) != 0;
                bool is_down = (message.lParam & (1 << 31)) == 0;
                
                if (was_down != is_down) {
                    if (vkcode >= 0 && vkcode < KEY_COUNT) {
                        win32_process_keyboard_message(&input->buttons[vkcode], is_down);
                    }
                }
            } break;
            
            case WM_MOUSEWHEEL: {
                // NOTE(Alexander): this only supports tick based scrolling
                // deltas are e.g. -2.0f, -1.0f, 1.0f
                // TODO(Alexander): we might want to have more values in between later
                s16 wheel_delta_x = (s16) ((u32) (message.wParam) & 0xFFFF);
                s16 wheel_delta_y = (s16) ((u32) (message.wParam >> 16) & 0xFFFF);
                f32 normalized_wheel_delta_x = (f32) wheel_delta_x / (f32) WHEEL_DELTA;
                f32 normalized_wheel_delta_y = (f32) wheel_delta_y / (f32) WHEEL_DELTA;
                input->mouse_wheel_delta = vec2(normalized_wheel_delta_x, normalized_wheel_delta_y);
            } break;
            
            default: {
                TranslateMessage(&message);
                DispatchMessageA(&message);
            } break;
        }
    }
    
    if (GetActiveWindow() == global_window) {
        win32_process_keyboard_message(&input->buttons[MOUSE_BUTTON_LEFT], GetKeyState(VK_LBUTTON) & (1 << 15));
        win32_process_keyboard_message(&input->buttons[MOUSE_BUTTON_RIGHT], GetKeyState(VK_RBUTTON) & (1 << 15));
        win32_process_keyboard_message(&input->buttons[MOUSE_BUTTON_MIDDLE], GetKeyState(VK_MBUTTON) & (1 << 15));
        win32_process_keyboard_message(&input->buttons[MOUSE_BUTTON_X1], GetKeyState(VK_XBUTTON1) & (1 << 15));
        win32_process_keyboard_message(&input->buttons[MOUSE_BUTTON_X2], GetKeyState(VK_XBUTTON2) & (1 << 15));
    } else {
        for (int i = 0; i < KEY_COUNT; i++) {
            input->buttons[i] = {};
        }
    }
}

// NOTE(Alexander): XInputGetState
#define X_INPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)
typedef X_INPUT_GET_STATE(x_input_get_state);
X_INPUT_GET_STATE(XInputGetStateStub) {
    return ERROR_DEVICE_NOT_CONNECTED;
}

static x_input_get_state* XInputGetState_;
#define XInputGetState XInputGetState_

// NOTE(Alexander): XInputSetState
#define X_INPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)
typedef X_INPUT_SET_STATE(x_input_set_state);
X_INPUT_SET_STATE(XInputSetStateStub) {
    return ERROR_DEVICE_NOT_CONNECTED;
}

static x_input_set_state* XInputSetState_;
#define XInputSetState XInputSetState_

static void
win32_load_xinput() {
    HMODULE xinput_library = LoadLibraryA("xinput1_4.dll");
    if (!xinput_library) {
        xinput_library = LoadLibraryA("xinput9_1_0.dll");
    }
    if (!xinput_library) {
        xinput_library = LoadLibraryA("xinput1_3.dll");
    }
    
    if (xinput_library) {
        XInputGetState = (x_input_get_state*) GetProcAddress(xinput_library, "XInputGetState");
        if (!XInputGetState) XInputGetState = &XInputGetStateStub;
        XInputSetState = (x_input_set_state*) GetProcAddress(xinput_library, "XInputSetState");
        if (!XInputSetState) XInputSetState = &XInputSetStateStub;
    } else {
        win32_warning("Could not find any xinput dll, gamepads will not be supported!");
    }
}

static inline Vec2
win32_process_xinput_stick(SHORT stick_x, SHORT stick_y, f32 deadzone) {
    Vec2 result;
    result.x = (f32) ((s32) stick_x + 32768) / 65535.0f;
    result.y = (f32) ((s32) stick_y + 32768) / 65535.0f;
    result = result*2.0f - 1.0f;
    result.y = -result.y; // NOTE(Alexander): y is flipped
    
    f32 sqr_length = length_sq(result);
    f32 sqr_deadzone = (f32) deadzone;
    if (sqr_length < sqr_deadzone) {
        result = vec2_zero;
    } else {
        f32 len = sqrt(sqr_length);
        result = result/len * ((len - deadzone) / (1 - deadzone));
    }
    
    return result;
}

static inline void
win32_process_xinput_digital_button(DWORD xinput_button_state,
                                    WORD xinput_button_mask,
                                    Input_Button_State* new_state,
                                    Input_Button_State* old_state) {
    new_state->ended_down = ((xinput_button_state & xinput_button_mask) == xinput_button_mask);
    new_state->num_half_transitions = (old_state->ended_down != new_state->ended_down) ? 1 : 0;
}

static inline void
win32_update_xinput() {
    DWORD max_gamepad_count = XUSER_MAX_COUNT;
    if (max_gamepad_count > fixed_array_count(acorn.input.gamepads)) {
        max_gamepad_count = fixed_array_count(acorn.input.gamepads);
    }
    
    for (DWORD gamepad_index = 0; gamepad_index < max_gamepad_count; gamepad_index++) {
        Input_Gamepad_State old_state = acorn.input.gamepads[gamepad_index];
        Input_Gamepad_State new_state = {};
        
        XINPUT_STATE xinput;
        if (XInputGetState && XInputGetState(gamepad_index, &xinput) == ERROR_SUCCESS) {
            new_state.is_connected = true;
            
            // TODO(Alexander): configurable
            f32 deadzone_left = 0.25f;
            f32 deadzone_right = 0.25f;
            XINPUT_GAMEPAD pad = xinput.Gamepad;
            new_state.left_stick = win32_process_xinput_stick(pad.sThumbLX, pad.sThumbLY,
                                                              deadzone_left);
            new_state.left_stick_move.ended_down = length_sq(new_state.left_stick) > 0.02f;
            new_state.left_stick_move.num_half_transitions = (old_state.left_stick_move.ended_down !=
                                                              new_state.left_stick_move.ended_down) ? 1: 0;
            
            new_state.right_stick = win32_process_xinput_stick(pad.sThumbRX, pad.sThumbRY,
                                                               deadzone_right);
            new_state.right_stick_move.ended_down = length_sq(new_state.right_stick) > 0.02f;
            new_state.right_stick_move.num_half_transitions = (old_state.right_stick_move.ended_down !=
                                                               new_state.right_stick_move.ended_down) ? 1: 0;
            
            win32_process_xinput_digital_button(pad.wButtons, XINPUT_GAMEPAD_DPAD_UP,
                                                &new_state.buttons[GAMEPAD_LEFT_FACE_UP],
                                                &old_state.buttons[GAMEPAD_LEFT_FACE_UP]);
            win32_process_xinput_digital_button(pad.wButtons, XINPUT_GAMEPAD_DPAD_RIGHT,
                                                &new_state.buttons[GAMEPAD_LEFT_FACE_RIGHT],
                                                &old_state.buttons[GAMEPAD_LEFT_FACE_RIGHT]);
            win32_process_xinput_digital_button(pad.wButtons, XINPUT_GAMEPAD_DPAD_DOWN,
                                                &new_state.buttons[GAMEPAD_LEFT_FACE_DOWN],
                                                &old_state.buttons[GAMEPAD_LEFT_FACE_DOWN]);
            win32_process_xinput_digital_button(pad.wButtons, XINPUT_GAMEPAD_DPAD_LEFT,
                                                &new_state.buttons[GAMEPAD_LEFT_FACE_LEFT],
                                                &old_state.buttons[GAMEPAD_LEFT_FACE_LEFT]);
            
            win32_process_xinput_digital_button(pad.wButtons, XINPUT_GAMEPAD_Y,
                                                &new_state.buttons[GAMEPAD_RIGHT_FACE_UP],
                                                &old_state.buttons[GAMEPAD_RIGHT_FACE_UP]);
            win32_process_xinput_digital_button(pad.wButtons, XINPUT_GAMEPAD_B,
                                                &new_state.buttons[GAMEPAD_RIGHT_FACE_RIGHT],
                                                &old_state.buttons[GAMEPAD_RIGHT_FACE_RIGHT]);
            win32_process_xinput_digital_button(pad.wButtons, XINPUT_GAMEPAD_A,
                                                &new_state.buttons[GAMEPAD_RIGHT_FACE_DOWN],
                                                &old_state.buttons[GAMEPAD_RIGHT_FACE_DOWN]);
            win32_process_xinput_digital_button(pad.wButtons, XINPUT_GAMEPAD_X,
                                                &new_state.buttons[GAMEPAD_RIGHT_FACE_LEFT],
                                                &old_state.buttons[GAMEPAD_RIGHT_FACE_LEFT]);
            
            const s32 trigger_threshold = 255/2; // TODO(Alexander): configurable
            win32_process_xinput_digital_button(pad.wButtons, XINPUT_GAMEPAD_LEFT_SHOULDER,
                                                &new_state.buttons[GAMEPAD_LEFT_BUMPER],
                                                &old_state.buttons[GAMEPAD_LEFT_BUMPER]);
            win32_process_xinput_digital_button(pad.bLeftTrigger > trigger_threshold ? 1: 0, 1,
                                                &new_state.buttons[GAMEPAD_LEFT_TRIGGER],
                                                &old_state.buttons[GAMEPAD_LEFT_TRIGGER]);
            
            win32_process_xinput_digital_button(pad.wButtons, XINPUT_GAMEPAD_RIGHT_SHOULDER,
                                                &new_state.buttons[GAMEPAD_RIGHT_BUMPER],
                                                &old_state.buttons[GAMEPAD_RIGHT_BUMPER]);
            win32_process_xinput_digital_button(pad.bRightTrigger > trigger_threshold ? 1: 0, 1,
                                                &new_state.buttons[GAMEPAD_RIGHT_TRIGGER],
                                                &old_state.buttons[GAMEPAD_RIGHT_TRIGGER]);
        }
        
        acorn.input.gamepads[gamepad_index] = new_state;
    }
}
#endif

inline s64
win32_get_high_resolution_frequency() {
    LARGE_INTEGER result; 
    QueryPerformanceFrequency(&result);
    return result.QuadPart;
}

inline s64
win32_get_high_resolution_time() {
    LARGE_INTEGER result;
    QueryPerformanceCounter(&result);
    return result.QuadPart;
}

typedef HGLRC WINAPI type_wglCreateContextAttribsARB(HDC hDC, 
                                                     HGLRC hshareContext,
                                                     const int *attribList);
type_wglCreateContextAttribsARB* wglCreateContextAttribsARB;

typedef BOOL WINAPI type_wglSwapIntervalEXT(int interval);
type_wglSwapIntervalEXT* wglSwapIntervalEXT;

inline bool
win32_create_opengl_context(HDC hdc) {
    // Let windows suggest a pixel format to use
    PIXELFORMATDESCRIPTOR desired_pfd;
    bzero(&desired_pfd, sizeof(PIXELFORMATDESCRIPTOR));
    desired_pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    desired_pfd.nVersion = 1;
    desired_pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
    desired_pfd.cColorBits = 32;
    desired_pfd.cAlphaBits = 8;
    desired_pfd.iLayerType = PFD_MAIN_PLANE;
    int pixel_format_index = ChoosePixelFormat(hdc, &desired_pfd);
    
    // Set the suggested pixel format
    PIXELFORMATDESCRIPTOR suggested_pfd;
    DescribePixelFormat(hdc, pixel_format_index, sizeof(suggested_pfd), &suggested_pfd);
    SetPixelFormat(hdc, pixel_format_index, &suggested_pfd);
    
    HGLRC opengl_rc = wglCreateContext(hdc);
    
    // Accepted as an attribute name in <*attribList>:
#define WGL_CONTEXT_MAJOR_VERSION_ARB           0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB           0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB             0x2093
#define WGL_CONTEXT_FLAGS_ARB                   0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB            0x9126
    
    // WGL_CONTEXT_FLAGS in <*attribList>:
#define WGL_CONTEXT_DEBUG_BIT_ARB               0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB  0x0002
    
    // WGL_CONTEXT_PROFILE_MASK_ARB in <*attribList>:
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB        0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
    
    // Error cods for wglCreateContextAttribsARB
#define ERROR_INVALID_VERSION_ARB               0x2095
#define ERROR_INVALID_PROFILE_ARB               0x2096
    
    if (wglMakeCurrent(hdc, opengl_rc)) {
        wglCreateContextAttribsARB = (type_wglCreateContextAttribsARB*) wglGetProcAddress("wglCreateContextAttribsARB");
        
        if (wglCreateContextAttribsARB) {
            int major = 3;
            int minor = 3;
            int attribs[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                WGL_CONTEXT_MINOR_VERSION_ARB, 3,
                WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB | WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                0,
            };
            //win32_show_error(string_print("attribs = %", attribs[7]));
            
            HGLRC share_opengl_rc = 0;
            HGLRC modern_opengl_rc = wglCreateContextAttribsARB(hdc, share_opengl_rc, attribs);
            
            if (modern_opengl_rc) {
                wglMakeCurrent(hdc, modern_opengl_rc);
                wglDeleteContext(opengl_rc);
                opengl_rc = modern_opengl_rc;
            } else {
                win32_fatal_error(cstring_print("OpenGL version %d.%d is not supported", major, minor));
            }
            
#define OPENGL_SET_FUNCPTR(name) opengl.name = (type_##name*) wglGetProcAddress(#name);
            OPENGL_SET_FUNCPTR(glGenBuffers);
            OPENGL_SET_FUNCPTR(glBindBuffer);
            OPENGL_SET_FUNCPTR(glBufferData);
            OPENGL_SET_FUNCPTR(glBufferSubData);
            OPENGL_SET_FUNCPTR(glGenVertexArrays);
            OPENGL_SET_FUNCPTR(glBindVertexArray);
            OPENGL_SET_FUNCPTR(glVertexAttribPointer);
            OPENGL_SET_FUNCPTR(glEnableVertexAttribArray);
            OPENGL_SET_FUNCPTR(glDrawArrays);
            OPENGL_SET_FUNCPTR(glDrawElements);
            OPENGL_SET_FUNCPTR(glCreateShader);
            OPENGL_SET_FUNCPTR(glDeleteShader);
            OPENGL_SET_FUNCPTR(glShaderSource);
            OPENGL_SET_FUNCPTR(glCompileShader);
            OPENGL_SET_FUNCPTR(glAttachShader);
            OPENGL_SET_FUNCPTR(glGetShaderiv);
            OPENGL_SET_FUNCPTR(glGetShaderInfoLog);
            OPENGL_SET_FUNCPTR(glGetProgramiv);
            OPENGL_SET_FUNCPTR(glGetProgramInfoLog);
            OPENGL_SET_FUNCPTR(glCreateProgram);
            OPENGL_SET_FUNCPTR(glLinkProgram);
            OPENGL_SET_FUNCPTR(glUseProgram);
            OPENGL_SET_FUNCPTR(glGetUniformLocation);
            OPENGL_SET_FUNCPTR(glUniformMatrix4fv);
            OPENGL_SET_FUNCPTR(glUniform1iv);
            OPENGL_SET_FUNCPTR(glActiveTexture);
            OPENGL_SET_FUNCPTR(glGenerateMipmap);
            OPENGL_SET_FUNCPTR(glBindFramebuffer);
            OPENGL_SET_FUNCPTR(glGenFramebuffers);
            OPENGL_SET_FUNCPTR(glDeleteFramebuffers);
            OPENGL_SET_FUNCPTR(glCheckFramebufferStatus);
            OPENGL_SET_FUNCPTR(glFramebufferTexture2D);
            OPENGL_SET_FUNCPTR(glBlendEquation);
            
#if BUILD_INTERNAL
            OPENGL_SET_FUNCPTR(glDebugMessageCallback);
            OPENGL_SET_FUNCPTR(glDebugMessageControl);
#endif
            
            // Also define pointers to opengl32.dll functions
            HMODULE wgl32 = LoadLibraryA("opengl32.dll");
#define WGL32_SET_FUNCPTR(name) opengl.name = (type_##name*) GetProcAddress(wgl32, #name);
            WGL32_SET_FUNCPTR(glEnable);
            WGL32_SET_FUNCPTR(glDisable);
            WGL32_SET_FUNCPTR(glViewport);
            WGL32_SET_FUNCPTR(glClear);
            WGL32_SET_FUNCPTR(glClearColor);
            WGL32_SET_FUNCPTR(glBlendFunc);
            WGL32_SET_FUNCPTR(glScissor);
            WGL32_SET_FUNCPTR(glGenTextures);
            WGL32_SET_FUNCPTR(glBindTexture);
            WGL32_SET_FUNCPTR(glTexParameteri);
            WGL32_SET_FUNCPTR(glTexImage2D);
            
            // Enable VSync
            // TODO(Alexander): I think most want this enabled but we can add a way to turn off later
            wglSwapIntervalEXT = (type_wglSwapIntervalEXT*) wglGetProcAddress("wglSwapIntervalEXT");
            if(wglSwapIntervalEXT) {
                wglSwapIntervalEXT(1);
            }
            
            return true;
        } else {
            printf("[WIN32] Failed to intialize Modern OpenGL!");
        }
    } else {
        // TODO(Alexander): proper logging
        printf("Failed to intialize OpenGL!\n");
    }
    
    return false;
}

void
win32_swap_buffers(HDC device_context) {
    SwapBuffers(device_context);
}

int start_main_loop();

void
main() {
    // Enable UTF-8 encoding
    SetConsoleOutputCP(65001);

    HINSTANCE h_instance = GetModuleHandleA(0);
    
    sleep_is_granular = timeBeginPeriod(1) == TIMERR_NOERROR;

    int width = 640;
    int height = 480;
    const char* title = "The Legend of Zelda: Ocarina of Time";
    
    WNDCLASSA wndclass;
    bzero(&wndclass, sizeof(WNDCLASSA));
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = &win32_main_callback;
    wndclass.hInstance = h_instance;
    wndclass.lpszClassName = "OOTClass";
    wndclass.hCursor = LoadCursor(0, IDC_ARROW);
    
    if (!RegisterClassA(&wndclass)) {
        win32_fatal_error("Failed start the application");
    }
    
    HWND window = CreateWindowExA(0,
                                  wndclass.lpszClassName,
                                  title,
                                  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                  CW_USEDEFAULT,
                                  CW_USEDEFAULT,
                                  width, height,
                                  0, 0,
                                  h_instance,
                                  0);
    
    if (!window) {
        win32_fatal_error("Failed start the application");
    }
    
    HDC device_context = GetDC(window);
    
    // TODO(alexander): how do we reliably query the refresh rate on windows?
    int monitor_refresh_hz = 60;
    int win32_refresh_rate = GetDeviceCaps(device_context, VREFRESH);
    if (win32_refresh_rate > 1) {
        monitor_refresh_hz = win32_refresh_rate;
    }
    int game_update_hz = monitor_refresh_hz;
    target_seconds_per_frame = 1.0 / (f64) game_update_hz;
    global_delta_time = (f32) target_seconds_per_frame;
    pln("[WIN32] target FPS = %d\n", game_update_hz);
    
    // void* memory = VirtualAlloc(0, gigabytes(1), MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    // if (!memory) {
    //     win32_fatal_error("Failed reserve 1GB of virtual memory");
    // }
    
    // win32_load_xinput();
    
    if (win32_create_opengl_context(device_context)) {
        global_window = window;
        global_device_context = device_context;

        init_opengl();

        start_main_loop();
        
    } else {
        win32_fatal_error("Failed to setup OpenGL");
    }
}


// TODO(Alexander): I think we should make a window struct isntead
bool
is_fullscreen_mode() {
    return global_fullscreen;
}

void
set_fullscreen_mode(bool fullscreen) {
    global_fullscreen = fullscreen;
    if (fullscreen) {
        SetWindowLongPtr(global_window, GWL_STYLE, WS_POPUP);
        ShowWindow(global_window, SW_SHOWMAXIMIZED);
    } else {
        SetWindowLongPtr(global_window, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        ShowWindow(global_window, SW_SHOWDEFAULT);
    }
}

int
start_main_loop() {
    global_is_running = true;
    
    s64 counter_freq = win32_get_high_resolution_frequency();
    s64 last_counter = win32_get_high_resolution_time();

    // TODO: hardcoded size
    
    void* heap_memory = VirtualAlloc(0, 0x400000, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    MainTest(0, heap_memory);

    while (global_is_running) {
        // Input
        win32_process_pending_messages();
        // win32_process_pending_messages(&acorn.input);
        
        RECT rect;
        GetClientRect(global_window, &rect);
        opengl.glViewport(0, 0, rect.right, rect.bottom);
        // acorn.screen_size = vec2((f32) rect.right, (f32) rect.bottom);
        // acorn.render_size = acorn.screen_size;
        
        // Vec2 mouse_position = acorn.input.mouse_position;
        // if (GetActiveWindow() == global_window) {
        //     POINT mouse_pt;
        //     GetCursorPos(&mouse_pt);
        //     ScreenToClient(global_window, &mouse_pt);
        //     mouse_position = vec2((f32) mouse_pt.x, (f32) mouse_pt.y);
        // }
        // acorn.input.mouse_delta = mouse_position - acorn.input.mouse_position;
        // acorn.input.mouse_position = mouse_position;
        
        // win32_update_xinput();
        
        // input_update_actions(&acorn.input);
        
        // if (is_key_down(KEY_ALT) && is_key_pressed(KEY_F4)) {
        //     stop_main_loop();
        // }
        
        // Main game loop
        //opengl.glScissor((int) 0, (int) 0,
        //(int) acorn.render_size.width, (int) acorn.render_size.height);
        // set_default_shader();
        // set_clip_rectangle(rectangle(vec2_zero, acorn.render_size));
        // set_default_camera();
        // set_blend_mode(BLEND_MODE_ALPHA);
        // callback(data);
        // flush_batch(acorn.curr_batch);


        
        render_test(rect.right, rect.bottom);
        
        win32_swap_buffers(global_device_context);

        Sleep(20);
        
        // Check time and limit framerate
        // s64 end_counter = win32_get_high_resolution_time();
        // f64 seconds_elapsed_for_frame = (f64) (end_counter - last_counter) / (f64) counter_freq;
        // if (seconds_elapsed_for_frame < target_seconds_per_frame) {
        //     if (sleep_is_granular) {
        //         DWORD sleep_ms = (DWORD) (1000.0 * (target_seconds_per_frame -
        //                                             seconds_elapsed_for_frame));
        //         if (sleep_ms > 0) {
        //             Sleep(sleep_ms);
        //         }
        //     } else {
        //         // TODO(Alexander): implement other way without sleep
        //         assert(0 && "unimplemented");
        //     }
        // } else {
        //     // TODO(alexander): missed frame rate, logging!
        // }
        
        //pln("frametime: %f ms", seconds_elapsed_for_frame*1000.0);
        
        // Delta time
        // end_counter = win32_get_high_resolution_time();
        // global_delta_time = (f32) (end_counter - last_counter) / (f32) counter_freq;
        //pln("delta_time: %f ms", delta_time*1000.0);
        // last_counter = end_counter;
    }
    
    return 0;
}