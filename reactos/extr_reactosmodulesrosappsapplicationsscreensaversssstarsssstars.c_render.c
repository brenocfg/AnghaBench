#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int uiRotation; unsigned int uiNumStars; scalar_t__ uiSpeed; } ;
struct TYPE_3__ {float x1; float y1; scalar_t__ z; float x2; float y2; } ;

/* Variables and functions */
 scalar_t__ FAR_PLANE ; 
 float FIELD_HEIGHT ; 
 float FIELD_WIDTH ; 
 scalar_t__ GAP ; 
 int /*<<< orphan*/  GL_ONE ; 
 int /*<<< orphan*/  GL_QUADS ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 scalar_t__ NEAR_PLANE ; 
 float RAND_MAX ; 
#define  ROTATION_LINEAR 129 
#define  ROTATION_PERIODIC 128 
 TYPE_2__ Settings ; 
 TYPE_1__* Vertex ; 
 int cos (float) ; 
 float fAngle ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glColor3ub (int,int,int) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glRotatef (float,float,float,float) ; 
 int /*<<< orphan*/  glTexCoord2f (float,float) ; 
 int /*<<< orphan*/  glVertex3f (float,float,scalar_t__) ; 
 scalar_t__ rand () ; 

__attribute__((used)) static void
render(void)
{
    unsigned int i;
    float        fSpin;
    float        fSpeed;
    float        xp, yp;

    // Initialize current speed
    fSpeed = (float)Settings.uiSpeed / 100.f;

    glEnable(GL_TEXTURE_2D);                // Enable Texture Mapping

    glBlendFunc(GL_SRC_ALPHA,GL_ONE);           // Set The Blending Function For Translucency

    switch (Settings.uiRotation) {
    case ROTATION_LINEAR:
        fAngle += fSpeed;
        glRotatef( fAngle, 0.0f, 0.0f, 1.0f );
        break;

    case ROTATION_PERIODIC:
        fAngle += fSpeed / 75.f;
        fSpin = (float)(50. * cos(fAngle));
        glRotatef( fSpin, 0.0f, 0.0f, 1.0f );
        break;
    }

    glColor3ub(255, 255, 255);

    glBegin(GL_QUADS);              // Begin Drawing The Textured Quad

    // Draw the stars
    for (i = 0; i < Settings.uiNumStars; i++)
    {
        glTexCoord2f(0.0f, 0.0f); glVertex3f(Vertex[i].x1, Vertex[i].y1, Vertex[i].z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(Vertex[i].x2, Vertex[i].y1, Vertex[i].z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(Vertex[i].x2, Vertex[i].y2, Vertex[i].z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(Vertex[i].x1, Vertex[i].y2, Vertex[i].z);

        // increment z
        Vertex[i].z += fSpeed;

        // check to see if passed view
        if( Vertex[i].z > NEAR_PLANE + GAP ||
            Vertex[i].z < FAR_PLANE )
        {
            xp = ( (float) rand() / RAND_MAX - .5f ) * FIELD_WIDTH;
            yp = ( (float) rand() / RAND_MAX - .5f ) * FIELD_HEIGHT;

            Vertex[i].x1 = -1.f + xp;
            Vertex[i].y1 = -1.f + yp;
            Vertex[i].x2 =  1.f + xp;
            Vertex[i].y2 =  1.f + yp;
            Vertex[i].z  = FAR_PLANE;
        }
    }

    glEnd();                    // Done Drawing The Textured Quad

    glDisable(GL_TEXTURE_2D);               // Enable Texture Mapping
}