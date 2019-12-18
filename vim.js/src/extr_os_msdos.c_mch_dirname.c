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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int FAIL ; 
 int OK ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 int /*<<< orphan*/  slash_adjust (int /*<<< orphan*/ *) ; 

int
mch_dirname(
    char_u	*buf,
    int		len)
{
#ifdef DJGPP
    if (getcwd((char *)buf, len) == NULL)
	return FAIL;
    /* turn the '/'s returned by DJGPP into '\'s */
    slash_adjust(buf);
    return OK;
#else
    return (getcwd((char *)buf, len) != NULL ? OK : FAIL);
#endif
}