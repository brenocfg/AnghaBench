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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_3__ {char* input_name; int line_number; scalar_t__ near_text; } ;
typedef  TYPE_1__ loc_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  make_print (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ want_near_indication ; 
 char* xstrdup (scalar_t__) ; 

__attribute__((used)) static void generic_msg(const loc_info_t *loc_info, const char *s, const char *t, va_list ap)
{
	fprintf(stderr, "%s:%d: %s: ", loc_info->input_name, loc_info->line_number, t);
	vfprintf(stderr, s, ap);

	if (want_near_indication)
	{
		char *cpy;
		if(loc_info->near_text)
		{
			cpy = xstrdup(loc_info->near_text);
			make_print(cpy);
			fprintf(stderr, " near '%s'", cpy);
			free(cpy);
		}
	}
}