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
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  FLT_MAX ; 
 scalar_t__ errno ; 
 float fz_clamp (float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float fz_strtof (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ isnan (float) ; 

float fz_atof(const char *s)
{
	float result;

	if (s == NULL)
		return 0;

	errno = 0;
	result = fz_strtof(s, NULL);
	if ((errno == ERANGE && result == 0) || isnan(result))
		/* Return 1.0 on  underflow, as it's a small known value that won't cause a divide by 0.  */
		return 1;
	result = fz_clamp(result, -FLT_MAX, FLT_MAX);
	return result;
}