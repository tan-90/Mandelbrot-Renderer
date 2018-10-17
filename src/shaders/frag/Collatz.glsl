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

int IterMax  = 10000;

void main()
{
	int a;
	int b;

	int n;

	int Iter;

	a = int(floor(uGraphRange.MinX + FragPosition.x * uGraphSize.x));
	b = int(floor(uGraphRange.MinY + FragPosition.y * uGraphSize.y));

	Iter = 0;

	n = 43; // ?

	while(n != 1 && Iter < IterMax)
	{
		Iter++;

		if(n % 2 == 0)
		{
			n /= 2;
		} else
		{
			n *= a;
			n += b;
		}
	}
	
	float IterParam = clamp(float(Iter/float(IterMax)) * 200, 0.0, 1.0);

	if(Iter < IterMax)
	{
		Color = vec4(vec3(IterParam, 0.0, 0.0), 1.0);
	} else
	{
		Color = vec4(vec3(1.0 - IterParam, 0.0, 0.0), 1.0);
	}
		
}