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

int
mch_isFullName(char_u *fname)
{
    /* A name like "d:/foo" and "//server/share" is absolute */
    return (fname[0] != NUL && fname[1] == ':'
				     && (fname[2] == '/' || fname[2] == '\\'))
	|| (fname[0] == fname[1] && (fname[0] == '/' || fname[0] == '\\'));
}