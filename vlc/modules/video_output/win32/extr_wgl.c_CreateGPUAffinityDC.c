#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * affinityHDC; int /*<<< orphan*/  hvideownd; } ;
typedef  TYPE_1__ vout_display_sys_t ;
struct TYPE_6__ {TYPE_1__* sys; } ;
typedef  TYPE_2__ vlc_gl_t ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  PIXELFORMATDESCRIPTOR ;
typedef  int /*<<< orphan*/  (* PFNWGLENUMGPUSNVPROC ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ;
typedef  int /*<<< orphan*/ * (* PFNWGLCREATEAFFINITYDCNVPROC ) (int /*<<< orphan*/ **) ;
typedef  int /*<<< orphan*/ * HGPUNV ;
typedef  int /*<<< orphan*/  HGLRC ;
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 int /*<<< orphan*/  ChoosePixelFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPixelFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_PFD_INITIALIZER ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglCreateContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wglDeleteContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglGetProcAddress (char*) ; 
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CreateGPUAffinityDC(vlc_gl_t *gl, UINT nVidiaAffinity) {
    vout_display_sys_t *sys = gl->sys;

    PIXELFORMATDESCRIPTOR pfd = VLC_PFD_INITIALIZER;

    /* create a temporary GL context */
    HDC winDC = GetDC(sys->hvideownd);
    SetPixelFormat(winDC, ChoosePixelFormat(winDC, &pfd), &pfd);
    HGLRC hGLRC = wglCreateContext(winDC);
    wglMakeCurrent(winDC, hGLRC);

    /* Initialize the necessary function pointers */
    PFNWGLENUMGPUSNVPROC fncEnumGpusNV = (PFNWGLENUMGPUSNVPROC)wglGetProcAddress("wglEnumGpusNV");
    PFNWGLCREATEAFFINITYDCNVPROC fncCreateAffinityDCNV = (PFNWGLCREATEAFFINITYDCNVPROC)wglGetProcAddress("wglCreateAffinityDCNV");

    /* delete the temporary GL context */
    wglDeleteContext(hGLRC);

    /* see if we have the extensions */
    if (!fncEnumGpusNV || !fncCreateAffinityDCNV) return;

    /* find the graphics card */
    HGPUNV GpuMask[2];
    GpuMask[0] = NULL;
    GpuMask[1] = NULL;
    HGPUNV hGPU;
    if (!fncEnumGpusNV(nVidiaAffinity, &hGPU)) return;

    /* make the affinity DC */
    GpuMask[0] = hGPU;
    sys->affinityHDC = fncCreateAffinityDCNV(GpuMask);
    if (sys->affinityHDC == NULL) return;
    SetPixelFormat(sys->affinityHDC,
        ChoosePixelFormat(sys->affinityHDC, &pfd), &pfd);

    msg_Dbg(gl, "GPU affinity set to adapter: %d", nVidiaAffinity);
}