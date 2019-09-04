#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int GLsizei ;
typedef  int GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_LEQUAL ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_NICEST ; 
 int /*<<< orphan*/  GL_ONE ; 
 int /*<<< orphan*/  GL_PERSPECTIVE_CORRECTION_HINT ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  GL_SMOOTH ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  LoadGLTextures () ; 
 int /*<<< orphan*/  SetObject (int) ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glClearDepth (float) ; 
 int /*<<< orphan*/  glDepthFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glShadeModel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gluPerspective (float,int,float,float) ; 

void InitOpenGL(GLsizei width, GLsizei height)
{
    int loop;

	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective (45.0f, (GLfloat)(width)/(GLfloat)(height),1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();
		// Start Of User Initialization
	LoadGLTextures();									// Load The Textures From Our Resource File

	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth (1.0f);								// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);							// The Type Of Depth Testing (Less Or Equal)
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glShadeModel (GL_SMOOTH);							// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Set Perspective Calculations To Most Accurate
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBlendFunc(GL_ONE,GL_SRC_ALPHA);					// Set Blending Mode (Cheap / Quick)
	glEnable(GL_BLEND);


	for (loop=0; loop<50; loop++)					// Loop To Initialize 50 Objects
	{
		SetObject(loop);										// Call SetObject To Assign New Random Values
	}

}