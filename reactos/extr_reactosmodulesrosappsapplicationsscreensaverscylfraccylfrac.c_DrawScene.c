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
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  BeginPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DrawCylinder (int /*<<< orphan*/ ,int,double) ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  HLStoRGB (int,double,double,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SwapBuffers (int /*<<< orphan*/ ) ; 
 int angle ; 
 int /*<<< orphan*/  bval ; 
 int colorh ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glRotatef (int,double,double,double) ; 
 int /*<<< orphan*/  gval ; 
 int /*<<< orphan*/  lvls ; 
 int /*<<< orphan*/  rval ; 

void DrawScene(HWND hwnd, HDC dc, int ticks)
{
    PAINTSTRUCT ps;
    dc = BeginPaint(hwnd, &ps);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(ticks * 0.01, 0.0, 1.0, -0.5);
    angle += ticks * 0.01;
    colorh += ticks * 0.003;
    if (colorh > 360.0) colorh -= 360.0;
    HLStoRGB(colorh, 1.0, 0.7, &rval, &gval, &bval);
    DrawCylinder(lvls, angle, 0.2);
    SwapBuffers(dc);
    EndPaint(hwnd, &ps);
}