#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * affinityHDC; int /*<<< orphan*/  hvideownd; } ;
typedef  TYPE_1__ vout_display_sys_t ;
struct TYPE_5__ {TYPE_1__* sys; } ;
typedef  TYPE_2__ vlc_gl_t ;
typedef  int /*<<< orphan*/  PIXELFORMATDESCRIPTOR ;
typedef  int /*<<< orphan*/  (* PFNWGLDELETEDCNVPROC ) (int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  HGLRC ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  ChoosePixelFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPixelFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_PFD_INITIALIZER ; 
 int /*<<< orphan*/  wglCreateContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglDeleteContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglGetProcAddress (char*) ; 
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DestroyGPUAffinityDC(vlc_gl_t *gl) {
    vout_display_sys_t *sys = gl->sys;

    if (sys->affinityHDC == NULL) return;

    PIXELFORMATDESCRIPTOR pfd = VLC_PFD_INITIALIZER;

    /* create a temporary GL context */
    HDC winDC = GetDC(sys->hvideownd);
    SetPixelFormat(winDC, ChoosePixelFormat(winDC, &pfd), &pfd);
    HGLRC hGLRC = wglCreateContext(winDC);
    wglMakeCurrent(winDC, hGLRC);

    /* Initialize the necessary function pointers */
    PFNWGLDELETEDCNVPROC fncDeleteDCNV = (PFNWGLDELETEDCNVPROC)wglGetProcAddress("wglDeleteDCNV");

    /* delete the temporary GL context */
    wglDeleteContext(hGLRC);

    /* see if we have the extensions */
    if (!fncDeleteDCNV) return;

    /* delete the affinity DC */
    fncDeleteDCNV(sys->affinityHDC);
}