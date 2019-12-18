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
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 char* _StrError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toggle_default_locale () ; 

const char* StrError(DWORD error_code, BOOL use_default_locale)
{
	const char* ret;
	if (use_default_locale)
		toggle_default_locale();
	ret = _StrError(error_code);
	if (use_default_locale)
		toggle_default_locale();
	return ret;
}