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
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  int /*<<< orphan*/  FARPROC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InterlockedCompareExchangePointer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LoadLibraryW (char*) ; 
 int /*<<< orphan*/  OpenGLInitFunction (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  glChoosePixelFormat ; 
 int /*<<< orphan*/  glDescribePixelFormat ; 
 int /*<<< orphan*/  glGetPixelFormat ; 
 int /*<<< orphan*/  glSetPixelFormat ; 
 int /*<<< orphan*/  glSwapBuffers ; 
 int /*<<< orphan*/  hOpenGL ; 

__attribute__((used)) static BOOL OpenGLEnable(void)
{
    HMODULE hModOpengl32;
    BOOL Ret = TRUE;

    hModOpengl32 = LoadLibraryW(L"OPENGL32.DLL");
    if (hModOpengl32 == NULL)
        return FALSE;

    if (InterlockedCompareExchangePointer((PVOID*)&hOpenGL,
                                          (PVOID)hModOpengl32,
                                          NULL) != NULL)
    {
        FreeLibrary(hModOpengl32);

        /* NOTE: Even though another thread was faster loading the
                 library we can't just bail out here. We really need
                 to *try* to locate every function. This is slow but
                 thread-safe */
    }

    /* The cast is required on x64, because FARPROC has INT_PTR sized return */
    if (!OpenGLInitFunction("wglChoosePixelFormat", (FARPROC*)&glChoosePixelFormat))
        Ret = FALSE;

    if (!OpenGLInitFunction("wglSetPixelFormat", (FARPROC*)&glSetPixelFormat))
        Ret = FALSE;

    if (!OpenGLInitFunction("wglSwapBuffers", (FARPROC*)&glSwapBuffers))
        Ret = FALSE;

    if (!OpenGLInitFunction("wglDescribePixelFormat", (FARPROC*)&glDescribePixelFormat))
        Ret = FALSE;

    if (!OpenGLInitFunction("wglGetPixelFormat", (FARPROC*)&glGetPixelFormat))
        Ret = FALSE;

    return Ret;
}