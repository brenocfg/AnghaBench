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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  UU_ERROR_UNKNOWN ; 
 int /*<<< orphan*/  _uu_main_error ; 
 scalar_t__ _uu_main_thread ; 
 scalar_t__ pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_error_key ; 
 scalar_t__ uu_error_key_setup ; 

uint32_t
uu_error(void)
{
	if (_uu_main_thread)
		return (_uu_main_error);

	if (uu_error_key_setup < 0)	/* can't happen? */
		return (UU_ERROR_UNKNOWN);

	/*
	 * Because UU_ERROR_NONE == 0, if uu_set_error() was
	 * never called, then this will return UU_ERROR_NONE:
	 */
	return ((uint32_t)(uintptr_t)pthread_getspecific(uu_error_key));
}