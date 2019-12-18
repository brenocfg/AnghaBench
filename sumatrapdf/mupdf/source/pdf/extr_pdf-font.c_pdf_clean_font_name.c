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
 char const*** base_font_names ; 
 scalar_t__ nelem (char const***) ; 
 int /*<<< orphan*/  strcmp_ignore_space (char const*,char const*) ; 

const char *pdf_clean_font_name(const char *fontname)
{
	int i, k;
	for (i = 0; i < (int)nelem(base_font_names); i++)
		for (k = 0; base_font_names[i][k]; k++)
			if (!strcmp_ignore_space(base_font_names[i][k], fontname))
				return base_font_names[i][0];
	return fontname;
}