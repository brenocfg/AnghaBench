#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t tex; float y; float spinz; float flap; float fi; scalar_t__ spinzi; scalar_t__ yi; int /*<<< orphan*/  z; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  SetObject (int) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 scalar_t__ dRotate ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glFlush () ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glRotatef (float,float,float,float) ; 
 int /*<<< orphan*/  glTexCoord2f (float,float) ; 
 int /*<<< orphan*/  glTranslatef (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertex3f (float,float,float) ; 
 TYPE_1__* obj ; 
 int /*<<< orphan*/ * texture ; 

void Display()
{
    int loop;
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer

	for (loop=0; loop<50; loop++)							// Loop Of 50 (Draw 50 Objects)
	{
		glLoadIdentity ();										// Reset The Modelview Matrix
		glBindTexture(GL_TEXTURE_2D, texture[obj[loop].tex]);	// Bind Our Texture
		glTranslatef(obj[loop].x,obj[loop].y,obj[loop].z);		// Position The Object
		glRotatef(45.0f,1.0f,0.0f,0.0f);						// Rotate On The X-Axis
		if (dRotate)
		{
			glRotatef((obj[loop].spinz),0.0f,0.0f,1.0f);			// Spin On The Z-Axis
		}
		glBegin(GL_TRIANGLES);									// Begin Drawing Triangles
			// First Triangle														    _____
			glTexCoord2f(1.0f,1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);				//	(2)|    / (1)
			glTexCoord2f(0.0f,1.0f); glVertex3f(-1.0f, 1.0f, obj[loop].flap);	//	   |  /
			glTexCoord2f(0.0f,0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);				//	(3)|/

			// Second Triangle
			glTexCoord2f(1.0f,1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);				//	       /|(1)
			glTexCoord2f(0.0f,0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);				//	     /  |
			glTexCoord2f(1.0f,0.0f); glVertex3f( 1.0f,-1.0f, obj[loop].flap);	//	(2)/____|(3)

		glEnd();												// Done Drawing Triangles

		obj[loop].y-=obj[loop].yi;								// Move Object Down The Screen
		obj[loop].spinz+=obj[loop].spinzi;						// Increase Z Rotation By spinzi
		obj[loop].flap+=obj[loop].fi;							// Increase flap Value By fi

		if (obj[loop].y<-18.0f)									// Is Object Off The Screen?
		{
			SetObject(loop);									// If So, Reassign New Values
		}

		if ((obj[loop].flap>1.0f) || (obj[loop].flap<-1.0f))	// Time To Change Flap Direction?
		{
			obj[loop].fi=-obj[loop].fi;							// Change Direction By Making fi = -fi
		}
	}

	Sleep(15);													// Create A Short Delay (15 Milliseconds)

	glFlush ();

}