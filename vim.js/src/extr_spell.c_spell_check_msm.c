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
 int FAIL ; 
 char NUL ; 
 int OK ; 
 int SBLOCKSIZE ; 
 int /*<<< orphan*/  VIM_ISDIGIT (char) ; 
 long compress_added ; 
 long compress_inc ; 
 long compress_start ; 
 int getdigits (char**) ; 
 char* p_msm ; 

int
spell_check_msm()
{
    char_u	*p = p_msm;
    long	start = 0;
    long	incr = 0;
    long	added = 0;

    if (!VIM_ISDIGIT(*p))
	return FAIL;
    /* block count = (value * 1024) / SBLOCKSIZE (but avoid overflow)*/
    start = (getdigits(&p) * 10) / (SBLOCKSIZE / 102);
    if (*p != ',')
	return FAIL;
    ++p;
    if (!VIM_ISDIGIT(*p))
	return FAIL;
    incr = (getdigits(&p) * 102) / (SBLOCKSIZE / 10);
    if (*p != ',')
	return FAIL;
    ++p;
    if (!VIM_ISDIGIT(*p))
	return FAIL;
    added = getdigits(&p) * 1024;
    if (*p != NUL)
	return FAIL;

    if (start == 0 || incr == 0 || added == 0 || incr > start)
	return FAIL;

    compress_start = start;
    compress_inc = incr;
    compress_added = added;
    return OK;
}