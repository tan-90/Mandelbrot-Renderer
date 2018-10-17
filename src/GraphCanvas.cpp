#include "GraphCanvas.h"

void GraphRange::MoveX(float Offset)
{
	MinX += Offset;
	MaxX += Offset;
}

void GraphRange::MoveY(float Offset)
{
	MinY += Offset;
	MaxY += Offset;
}

void GraphRange::ZoomX(float Offset)
{
	MinX += Offset;
	MaxX -= Offset;
}
void GraphRange::ZoomY(float Offset)
{
	MinY += Offset;
	MaxY -= Offset;
}

GraphCanvas::GraphCanvas(uint Width, uint Height, std::string Name, GraphRange InitialRange, InputInfo Input)
	:Canvas(Width, Height, Name)
{
	m_CanvasRange = InitialRange;
	m_InputInfo   = Input;
	LoadUniforms();
}

void GraphCanvas::Update()
{
	// TODO: is a 1 frame input delay worth the organization?
	Canvas::Update();

	bool UpdateUniforms = false;

	if (Input::GetInstance().GetKeyDown(COORD_DUMP))
	{
		system("cls");
		std::cout << "Coordinate dump:" << std::endl;
		std::cout << "(" << m_CanvasRange.MinX << ", " << m_CanvasRange.MinY << ")"<< std::endl;
		std::cout << "(" << m_CanvasRange.GetSizeX() << ", " << m_CanvasRange.GetSizeY() << ")" << std::endl;
	}

	if (Input::GetInstance().GetKeyDown(KEYPAD_UP))
	{
		m_CanvasRange.MoveY(m_InputInfo.NavigationSensibility);
		UpdateUniforms = true;
	}
	else if (Input::GetInstance().GetKeyDown(KEYPAD_DOWN))
	{
		m_CanvasRange.MoveY(-m_InputInfo.NavigationSensibility);
		UpdateUniforms = true;
	}

	if (Input::GetInstance().GetKeyDown(KEYPAD_LEFT))
	{
		m_CanvasRange.MoveX(-m_InputInfo.NavigationSensibility);
		UpdateUniforms = true;
	}
	else if (Input::GetInstance().GetKeyDown(KEYPAD_RIGHT))
	{
		m_CanvasRange.MoveX(m_InputInfo.NavigationSensibility);
		UpdateUniforms = true;
	}

	if (Input::GetInstance().GetScroll().y > 0)
	{
		float ZoomOffsetX = m_CanvasRange.GetSizeX() * m_InputInfo.ZoomSensibility / 2;
		float ZoomOffsetY = m_CanvasRange.GetSizeY() * m_InputInfo.ZoomSensibility / 2;

		m_CanvasRange.ZoomX(ZoomOffsetX);
		m_CanvasRange.ZoomY(ZoomOffsetY);

		Input::GetInstance().ClearScrollOffset();
		UpdateUniforms = true;
	}
	else if (Input::GetInstance().GetScroll().y < 0)
	{
		float ZoomOffsetX = m_CanvasRange.GetSizeX() * m_InputInfo.ZoomSensibility / 2;
		float ZoomOffsetY = m_CanvasRange.GetSizeY() * m_InputInfo.ZoomSensibility / 2;

		m_CanvasRange.ZoomX(-ZoomOffsetX);
		m_CanvasRange.ZoomY(-ZoomOffsetY);

		Input::GetInstance().ClearScrollOffset();
		UpdateUniforms = true;
	}

	if (UpdateUniforms)
	{
		LoadUniforms();
	}
}

void GraphCanvas::LoadUniforms()
{
	LoadUniformGraphRange(m_GraphRangeUniform, m_CanvasRange);
	LoadUniformGraphSize(m_GraphSizeUniform);
}

void GraphCanvas::LoadUniformGraphRange(std::string Location, GraphRange Range)
{
	LoadUniformFloat(Location + ".MinX", Range.MinX);
	LoadUniformFloat(Location + ".MinY", Range.MinY);
}


void GraphCanvas::LoadUniformGraphSize(std::string Location)
{
	LoadUniformFloat(Location + ".x", m_CanvasRange.GetSizeX());
	LoadUniformFloat(Location + ".y", m_CanvasRange.GetSizeY());
}
