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
struct TYPE_3__ {int value; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* color_map ; 
 int enum_name (int /*<<< orphan*/ ) ; 
 int io_fprintf (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static bool
save_option_color_name(FILE *file, int color)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(color_map); i++)
		if (color_map[i].value == color)
			return io_fprintf(file, " %-8s", enum_name(color_map[i].name));

	return io_fprintf(file, " color%d", color);
}