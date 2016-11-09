#version 400 core

out vec4 Color;

in vec3 FragPosition;

struct GraphRange
{
	float MinX;
	float MinY;
};

struct GraphSize
{
	float x;
	float y;
};

uniform GraphRange uGraphRange;
uniform GraphSize  uGraphSize ;

float Scale = 2;
int MaxIter  = 1500;
float CX = 0.35;
float CY = 0.35;

void main()
{
	float X;
	float Y;

	float X0;
	float Y0;

	int Iter;

	X = uGraphRange.MinX + FragPosition.x * uGraphSize.x;
	Y = uGraphRange.MinY + FragPosition.y * uGraphSize.y;

	X0 = X;
	Y0 = Y;

	Iter = 0;

	while(X * X + Y * Y <= 2 * 2 && Iter < MaxIter)
	{
		Iter++;

		float XTemp = X * X - Y * Y + CX;
		Y = 2 * X * Y + CY;
		X = XTemp;
	}
	
	if(Iter == MaxIter)
	{
		Color = vec4(0.0, 0.0, 0.0, 10);
	}else
	{
		float IterFloat = float(Iter);
		float MaxIterFloat = float(MaxIter);
		Color = vec4(0.6, 0.6, 0.6, 1.0);
	}
}