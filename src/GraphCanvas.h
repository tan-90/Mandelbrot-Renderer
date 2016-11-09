#pragma once

#include "Canvas.h"

/** 
  * Describes the numeric range the canvas represents.
  */
struct GraphRange
{
	float MinX;
	float MaxX;

	float MinY;
	float MaxY;
};

class GraphCanvas : public Canvas
{
public:
	GraphCanvas(uint Width, uint Height, std::string Name, GraphRange InitialRange);

	inline void SetCanvasRange(GraphRange CanvasRange) { m_CanvasRange = CanvasRange; }

protected:
	virtual void LoadUniforms() override;

	void LoadUniformGraphRange(std::string Location, GraphRange Range);
	void LoadUniformGraphSize(std::string Location);

	GraphRange m_CanvasRange;

	const std::string m_GraphRangeUniform = "uGraphRange";
	const std::string m_GraphSizeUniform = "uGraphSize";
};
