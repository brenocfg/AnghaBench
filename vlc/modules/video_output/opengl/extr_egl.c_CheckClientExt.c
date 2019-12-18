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
 int /*<<< orphan*/  EGL_EXTENSIONS ; 
 int /*<<< orphan*/  EGL_NO_DISPLAY ; 
 char* eglQueryString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vlc_gl_StrHasToken (char const*,char const*) ; 

__attribute__((used)) static bool CheckClientExt(const char *name)
{
    const char *exts = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
    return vlc_gl_StrHasToken(exts, name);
}