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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 double ZI_PERCENTAGE_MAX ; 
 double strtod (char const*,char**) ; 

__attribute__((used)) static int
parse_frequency(const char *str, uint32_t *percent)
{
	double val;
	char *post;

	val = strtod(str, &post);
	if (post == NULL || *post != '\0')
		return (EINVAL);

	/* valid range is [0.0001, 100.0] */
	val /= 100.0f;
	if (val < 0.000001f || val > 1.0f)
		return (ERANGE);

	/* convert to an integer for use by kernel */
	*percent = ((uint32_t)(val * ZI_PERCENTAGE_MAX));

	return (0);
}