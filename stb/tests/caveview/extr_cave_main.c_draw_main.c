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
 int /*<<< orphan*/  GL_BLEND ; 
 int GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_CW ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_GREATER ; 
 int /*<<< orphan*/  GL_LESS ; 
 int /*<<< orphan*/  GL_LIGHTING ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TRUE ; 
 float SDL_GetPerformanceCounter () ; 
 scalar_t__ SDL_GetPerformanceFrequency () ; 
 int /*<<< orphan*/ * camang ; 
 int /*<<< orphan*/ * camloc ; 
 int /*<<< orphan*/  draw_stats () ; 
 float end_time ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glClearDepth (int) ; 
 int /*<<< orphan*/  glColor3f (int,int,int) ; 
 int /*<<< orphan*/  glDepthFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDepthMask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFrontFace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glRotatef (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glTranslatef (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gluOrtho2D (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  player_zoom ; 
 int /*<<< orphan*/  render_caves (int /*<<< orphan*/ *) ; 
 float render_time ; 
 int screen_x ; 
 int screen_y ; 
 float start_time ; 
 int /*<<< orphan*/  stbgl_Perspective (int /*<<< orphan*/ ,int,int,double,int) ; 
 int /*<<< orphan*/  stbgl_initCamera_zup_facing_y () ; 

void draw_main(void)
{
   glEnable(GL_CULL_FACE);
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_LIGHTING);
   glEnable(GL_DEPTH_TEST);
   #ifdef REVERSE_DEPTH
   glDepthFunc(GL_GREATER);
   glClearDepth(0);
   #else
   glDepthFunc(GL_LESS);
   glClearDepth(1);
   #endif
   glDepthMask(GL_TRUE);
   glDisable(GL_SCISSOR_TEST);
   glClearColor(0.6f,0.7f,0.9f,0.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glColor3f(1,1,1);
   glFrontFace(GL_CW);
   glEnable(GL_TEXTURE_2D);
   glDisable(GL_BLEND);


   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   #ifdef REVERSE_DEPTH
   stbgl_Perspective(player_zoom, 90, 70, 3000, 1.0/16);
   #else
   stbgl_Perspective(player_zoom, 90, 70, 1.0/16, 3000);
   #endif

   // now compute where the camera should be
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   stbgl_initCamera_zup_facing_y();

   glRotatef(-camang[0],1,0,0);
   glRotatef(-camang[2],0,0,1);
   glTranslatef(-camloc[0], -camloc[1], -camloc[2]);

   start_time = SDL_GetPerformanceCounter();
   render_caves(camloc);
   end_time = SDL_GetPerformanceCounter();

   render_time = (end_time - start_time) / (float) SDL_GetPerformanceFrequency();

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,screen_x/2,screen_y/2,0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_BLEND);
   glDisable(GL_CULL_FACE);
   draw_stats();
}