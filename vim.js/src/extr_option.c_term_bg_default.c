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
 scalar_t__ STRCMP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_NAME ; 
 char* mch_getenv (char*) ; 
 char* vim_strrchr (char*,char) ; 

__attribute__((used)) static char_u *
term_bg_default()
{
#if defined(MSDOS) || defined(OS2) || defined(WIN3264)
    /* DOS console nearly always black */
    return (char_u *)"dark";
#else
    char_u	*p;

    if (STRCMP(T_NAME, "linux") == 0
	    || STRCMP(T_NAME, "screen.linux") == 0
	    || STRCMP(T_NAME, "cygwin") == 0
	    || STRCMP(T_NAME, "putty") == 0
	    || ((p = mch_getenv((char_u *)"COLORFGBG")) != NULL
		&& (p = vim_strrchr(p, ';')) != NULL
		&& ((p[1] >= '0' && p[1] <= '6') || p[1] == '8')
		&& p[2] == NUL))
	return (char_u *)"dark";
    return (char_u *)"light";
#endif
}