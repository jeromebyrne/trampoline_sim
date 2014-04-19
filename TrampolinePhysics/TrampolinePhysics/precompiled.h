#ifndef PRECOMPILED_H
#define PRECOMPILED_H
#include "targetver.h"
#include "resource.h"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
//#include <gl\glaux.h>
#include <mmsystem.h>
#include <cmath>
#include <stdio.h> 
#include <string.h>
#include <fstream>
#include <iostream>
#include <math.h>						// Header File For Windows Math Library		( ADD )
#include <stdio.h>						// Header File For Standard Input/Output	( ADD )
#include <stdarg.h>						// Header File For Variable Argument Routines	( ADD )
#include "GLwindow.h"
#include "texture.h"
#include "Vector2.h"
#include "Vector3.h"
#define PI 3.14159
#define BITMAP_ID 0x4D42				// the universal bitmap ID
#include <sstream>
#include "BasicCamera.h"
#include <list>
#include "Timing.h"
#include <map>
using namespace std;

enum SimObjectType
	{
		PASSIVE,
		ACTIVE
	};

enum m_render_mode // how the trampoline is displayed
	{
		FULL,
		WIREFRAME,
		COLLISION
	};

enum trampoline_properties
{
	VERY_LOOSE,
	LOOSE,
	MEDIUM,
	TIGHT
};
#include "SimObject.h"
#include "ForceGenerator.h"
#include "gravity.h"
#include "forwardEulerIntegrator.h"
#include "Medium.h"
#include "Spring.h"
#endif