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
int MaxIter  = 3000;
float CX = 0.35;
float CY = 0.35;

void main()
{
	highp float X;
	highp float Y;

	highp float X0;
	highp float Y0;

	int Iter;

	X = uGraphRange.MinX + FragPosition.x * uGraphSize.x;
	Y = uGraphRange.MinY + FragPosition.y * uGraphSize.y;

	X0 = X;//-0.7;
	Y0 = Y;//0.27015;

	Iter = 0;

	while(X * X + Y * Y <= 2 * 2 && Iter < MaxIter)
	{
		Iter++;

		float XTemp = X*X - Y*Y + X0;
		Y = 2 * X * Y + Y0;
		X = XTemp;
	}
	

		highp float IterFloat = float(Iter);
		highp float MaxIterFloat = float(MaxIter);
		highp float ExplosionRate = IterFloat / MaxIterFloat;
		Color = clamp(ExplosionRate*25, 0, 1) * vec4(1.0, 0.2, 0.2, 1.0);
		
}