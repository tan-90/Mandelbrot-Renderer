#include <iostream>
#include "Input.h"

Input Input::s_Instance;

void Input::Init()
{
	memset(m_Keys, 0, sizeof(m_Keys));
	memset(m_Buttons, 0, sizeof(m_Buttons));
}

void Input::UnpressAll()
{
	memset(m_Keys, 0, sizeof(m_Keys));
	memset(m_Buttons, 0, sizeof(m_Buttons));
}

void Input::ClearScrollOffset()
{
	m_Scroll.x = 0;
	m_Scroll.y = 0;
}

void KeyCallback(GLFWwindow* Window, int Key, int ScanCode, int Action, int Mods)
{
	Input::GetInstance().m_Keys[Key] = Action != GLFW_RELEASE;
}

void ButtonCallback(GLFWwindow* Window, int Button, int Action, int Mods)
{
	Input::GetInstance().m_Buttons[Button] = Action != GLFW_RELEASE;
}

void CursorCallback(GLFWwindow* Window, double Xpos, double Ypos)
{
	Input::GetInstance().m_Cursor.x = (float)Xpos;
	Input::GetInstance().m_Cursor.y = (float)Ypos;
}

void ScrollCallback(GLFWwindow* Window, double Xoffset, double Yoffset)
{
	Input::GetInstance().m_Scroll.x = (float)Xoffset;
	Input::GetInstance().m_Scroll.y = (float)Yoffset;
}
