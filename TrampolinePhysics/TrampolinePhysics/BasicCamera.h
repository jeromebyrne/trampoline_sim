#ifndef BASICCAMERA_H
#define BASICCAMERA_H

class BasicCamera
{
	
	public:
	float X;
	float Y;
	float Z;

	float ForwardX;
	float ForwardY;
	float ForwardZ;

	float xAngle;
	float yAngle;

	BasicCamera(void)
	{
		X = 0;
		Y = -50;
		Z = -100;
		ForwardX = 0;
		ForwardY = 1;
		ForwardZ = 0;

		xAngle = 10;
		yAngle = 135;
	}

	~BasicCamera(void)
	{
	}

	void Update()
	{
		glTranslatef(X,Y,Z);

		glRotatef(xAngle,1,0,0);
		glRotatef(yAngle,0,1,0);

		float moveSpeed = 3;

		if(GetAsyncKeyState(VK_LEFT) < 0)
		{
			yAngle -= moveSpeed;
		}
		else if(GetAsyncKeyState(VK_RIGHT) < 0)
		{
			yAngle += moveSpeed;
		}

		if(GetAsyncKeyState(VK_UP) < 0)
		{
			Y -= moveSpeed;
		}
		else if(GetAsyncKeyState(VK_DOWN) < 0)
		{
			Y += moveSpeed;
		}

	}

	void MoveForward(float speed)
	{
		X += ForwardX * speed;
		Y += ForwardY * speed;
		Z -= ForwardZ * speed;
	}
	void MoveBackward(float speed)
	{
		X -= ForwardX * speed;
		Y -= ForwardY * speed;
		Z += ForwardZ * speed;
	}
	void MoveLeft(float speed)
	{
		X -= speed;
	}
	void MoveRight(float speed)
	{
		X += speed;
	}
};
#endif
