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
typedef  int char_u ;

/* Variables and functions */
 int NUL ; 
 int* getcmdline (char,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_expr_line (int*) ; 
 int /*<<< orphan*/  vim_free (int*) ; 

int
get_expr_register()
{
    char_u	*new_line;

    new_line = getcmdline('=', 0L, 0);
    if (new_line == NULL)
	return NUL;
    if (*new_line == NUL)	/* use previous line */
	vim_free(new_line);
    else
	set_expr_line(new_line);
    return '=';
}