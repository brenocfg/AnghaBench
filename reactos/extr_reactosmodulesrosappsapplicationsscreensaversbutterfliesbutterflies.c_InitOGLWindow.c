#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nSize; int nVersion; int dwFlags; int cColorBits; int cDepthBits; } ;
typedef  TYPE_1__ PIXELFORMATDESCRIPTOR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HGLRC ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int ChoosePixelFormat (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  DescribePixelFormat (int /*<<< orphan*/ ,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int PFD_DOUBLEBUFFER ; 
 int PFD_DRAW_TO_WINDOW ; 
 int PFD_SUPPORT_OPENGL ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPixelFormat (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wglCreateContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HGLRC InitOGLWindow(HWND hWnd)
{
	HDC hDC = GetDC(hWnd);
	HGLRC hRC = 0;
	PIXELFORMATDESCRIPTOR pfd;
	int nFormat;

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 24;

	nFormat = ChoosePixelFormat(hDC, &pfd);
	DescribePixelFormat(hDC, nFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
	SetPixelFormat(hDC, nFormat, &pfd);

	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);

	ReleaseDC(hWnd, hDC);

	return hRC;
}