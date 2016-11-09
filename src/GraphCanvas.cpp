#include "GraphCanvas.h"

GraphCanvas::GraphCanvas(uint Width, uint Height, std::string Name, GraphRange InitialRange)
	:Canvas(Width, Height, Name)
{
	m_CanvasRange = InitialRange;
	LoadUniforms();
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
	LoadUniformFloat(Location + ".x", m_CanvasRange.MaxX - m_CanvasRange.MinX);
	LoadUniformFloat(Location + ".y", m_CanvasRange.MaxY - m_CanvasRange.MinY);
}
