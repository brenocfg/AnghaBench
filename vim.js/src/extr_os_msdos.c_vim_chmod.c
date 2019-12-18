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
typedef  char char_u ;

/* Variables and functions */
 char NUL ; 
 int STRLEN (char*) ; 
 int _chmod (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _rtl_chmod (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vim_chmod(char_u *name)
{
    char_u	*p;
    int		f;
    int		c = 0;

    /* chmod() can't handle a file name with a trailing slash, remove it.
     * But don't remove it for "/" or "c:/". */
    p = name + STRLEN(name);
    if (p > name)
	--p;
    if (p > name && (*p == '\\' || *p == '/') && p[-1] != ':')
    {
	c = *p;				/* remove trailing (back)slash */
	*p = NUL;
    }
    else
	p = NULL;
#if defined(__BORLANDC__) && (__BORLANDC__ > 0x410)
    /* this also sets the archive bit, supported by Borland C 4.0 and later,
     * where __BORLANDC__ is 0x450 (3.1 is 0x410) */
    f = _rtl_chmod((char *)name, 0, 0);
#else
    f = _chmod((char *)name, 0, 0);
#endif
    if (p != NULL)
	*p = c;				/* put back (back)slash */
    return f;
}