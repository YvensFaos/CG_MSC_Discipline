#ifndef __GLFW_WRAPPER__
#define __GLFW_WRAPPER__

#include "GLFW\glfw3.h"

typedef void (*loopCallback)(void);
typedef bool (*runningCallback)(void);
typedef void (*errorCallback)(int e, const char* description);
typedef void (*keyboadCallback)(GLFWwindow* window, int key, int scancode, int action, int mods);

class GLFWWrapper
{
public:
	static GLFWwindow* window;
private:
	static float ratio;
	static errorCallback error;
	static loopCallback callback;
	static runningCallback running;
	static keyboadCallback keyboard;
public: 
	static void error_callback(int e, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void initialize(loopCallback callback);
	static void loop_callback(loopCallback callback);
	static void running_callback(runningCallback callback);
	static void keyboard_callback(keyboadCallback callback);
	static void error_callback(errorCallback callback);
	static void glLoop(void);
	static void finalize(void);
};

#endif