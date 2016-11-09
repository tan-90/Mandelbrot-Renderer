#pragma once

#include "Common.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

class Input
{
	friend void KeyCallback(GLFWwindow* Window, int Key, int ScanCode, int Action, int Mods);
	friend void ButtonCallback(GLFWwindow* Window, int Button, int Action, int Mods);
	friend void CursorCallback(GLFWwindow* Window, double Xpos, double Ypos);
	friend void ScrollCallback(GLFWwindow* Window, double Xoffset, double Yoffset);

public:
	void Init();

	void UnpressAll();

	static inline Input& GetInstance() { return s_Instance; }

	inline const glm::vec2& GetCursor() { return m_Cursor; }
	inline const glm::vec2& GetScroll() { return m_Scroll; }
	// TODO: sanitize array indexing.
	inline bool GetKeyDown(uint Key) { return m_Keys[Key]; }
	inline bool GetButtonDown(uint Button) { return m_Buttons[Button]; }

private:
	static Input s_Instance;

	bool m_Keys[MAX_KEYS];
	bool m_Buttons[MAX_BUTTONS];

	glm::vec2 m_Cursor;

	glm::vec2 m_Scroll;
};
