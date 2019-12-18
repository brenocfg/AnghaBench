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

/* Variables and functions */
 int /*<<< orphan*/  GL_NORMAL_ARRAY ; 
 int /*<<< orphan*/  GL_VERTEX_ARRAY ; 
 unsigned int NB_BANDS ; 
 unsigned int SPECTRUM_WIDTH ; 
 int /*<<< orphan*/  drawBar () ; 
 int /*<<< orphan*/  glDisableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glPopMatrix () ; 
 int /*<<< orphan*/  glPushMatrix () ; 
 int /*<<< orphan*/  glScalef (float,float,float) ; 
 int /*<<< orphan*/  glTranslatef (float,float,float) ; 
 int /*<<< orphan*/  setBarColor (float) ; 

__attribute__((used)) static void drawBars(float heights[])
{
    glPushMatrix();
    glTranslatef(-2.f, 0.f, 0.f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    float w = SPECTRUM_WIDTH / NB_BANDS;
    for (unsigned i = 0; i < NB_BANDS; ++i)
    {
        glPushMatrix();
        glScalef(1.f, heights[i], 1.f);
        setBarColor(heights[i]);
        drawBar();
        glPopMatrix();

        glTranslatef(w, 0.f, 0.f);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glPopMatrix();
}