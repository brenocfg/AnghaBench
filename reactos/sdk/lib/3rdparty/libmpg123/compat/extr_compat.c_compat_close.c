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
 int _close (int) ; 
 int close (int) ; 

int compat_close(int infd)
{
#if (defined(WIN32) && !defined (__CYGWIN__)) /* MSDN says POSIX function is deprecated beginning in Visual C++ 2005 */
	return _close(infd);
#else
	return close(infd);
#endif
}