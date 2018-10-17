#pragma once

#include "Canvas.h"

/**
  * Configure the input keys.
  */
// TODO: Move this to a proper settings class.
#define KEYPAD_UP GLFW_KEY_UP
#define KEYPAD_DOWN GLFW_KEY_DOWN
#define KEYPAD_LEFT GLFW_KEY_LEFT
#define KEYPAD_RIGHT GLFW_KEY_RIGHT
#define COORD_DUMP GLFW_KEY_ENTER

/** 
  * Describes the numeric range the canvas represents.
  */
struct GraphRange
{
	float MinX;
	float MaxX;

	float MinY;
	float MaxY;

	void MoveX(float Offset);
	void MoveY(float Offset);

	void ZoomX(float Offset);
	void ZoomY(float Offset);

	inline float GetSizeX() const { return MaxX - MinX; }
	inline float GetSizeY() const { return MaxY - MinY; }
};

/**
  * Describes how input works on the canvas.
  */
struct InputInfo
{
	float NavigationSensibility;
	float ZoomSensibility;
};

class GraphCanvas : public Canvas
{
public:
	GraphCanvas(uint Width, uint Height, std::string Name, GraphRange InitialRange, InputInfo Input);

	inline void SetCanvasRange(GraphRange CanvasRange) { m_CanvasRange = CanvasRange; LoadUniforms(); }
	
	virtual void Update() override;

protected:
	virtual void LoadUniforms() override;

	void LoadUniformGraphRange(std::string Location, GraphRange Range);
	void LoadUniformGraphSize(std::string Location);

	GraphRange m_CanvasRange;
	InputInfo  m_InputInfo;

	const std::string m_GraphRangeUniform = "uGraphRange";
	const std::string m_GraphSizeUniform = "uGraphSize";
};
