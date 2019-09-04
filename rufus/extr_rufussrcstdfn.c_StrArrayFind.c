#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int int32_t ;
struct TYPE_3__ {size_t Index; int /*<<< orphan*/ * String; } ;
typedef  TYPE_1__ StrArray ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int32_t StrArrayFind(StrArray* arr, const char* str)
{
	uint32_t i;
	if ((str == NULL) || (arr == NULL) || (arr->String == NULL))
		return -1;
	for (i = 0; i<arr->Index; i++) {
		if (strcmp(arr->String[i], str) == 0)
			return (int32_t)i;
	}
	return -1;
}