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
 long FA_ARCH ; 
 int OK ; 
 int _chmod (char*,int,int) ; 
 int _rtl_chmod (char*,int,int) ; 

int
mch_setperm(
    char_u	*name,
    long	perm)
{
    perm |= FA_ARCH;	    /* file has changed, set archive bit */
#if defined(__BORLANDC__) && (__BORLANDC__ > 0x410)
    return (_rtl_chmod((char *)name, 1, (int)perm) == -1 ? FAIL : OK);
#else
    return (_chmod((char *)name, 1, (int)perm) == -1 ? FAIL : OK);
#endif
}