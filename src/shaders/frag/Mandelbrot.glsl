#version 330 core

out vec4 Color;

in vec3 FragPosition;

float Scale = 2;
int MaxIter  = 10000;
float C = 0.25;

void main()
{
	float X;
	float Y;

	float X0;
	float Y0;

	int Iter;

	X = FragPosition.x - 0.5;
	Y = FragPosition.y;

	X /= 0.75;
	Y /= 0.75;

	X0 = X;
	Y0 = Y;

	Iter = 0;

	while(X * X + Y * Y <= 2 * 2 && Iter < MaxIter)
	{
		Iter++;

		float XTemp = X * X - Y * Y + X0;
		Y = 2 * X * Y + Y0;
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