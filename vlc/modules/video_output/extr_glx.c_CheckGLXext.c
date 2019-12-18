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
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 char* glXQueryExtensionsString (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,size_t const) ; 
 size_t strcspn (char const*,char*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strspn (char const*,char*) ; 

__attribute__((used)) static bool CheckGLXext (Display *dpy, unsigned snum, const char *ext)
{
    const char *exts = glXQueryExtensionsString (dpy, snum);
    const size_t extlen = strlen (ext);

    while (*exts)
    {
        exts += strspn (exts, " ");

        size_t len = strcspn (exts, " ");
        if (len == extlen && !memcmp (exts, ext, extlen))
            return true;
        exts += len;
    }
    return false;
}