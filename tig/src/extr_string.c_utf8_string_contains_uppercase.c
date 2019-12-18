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
 int /*<<< orphan*/  UTF8PROC_CATEGORY_LU ; 
 int utf8_string_contains (char const*,int /*<<< orphan*/ ) ; 

bool
utf8_string_contains_uppercase(const char *search)
{
	return utf8_string_contains(search, UTF8PROC_CATEGORY_LU);
}