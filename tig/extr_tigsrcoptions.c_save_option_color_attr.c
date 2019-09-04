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
 TYPE_1__* attr_map ; 
 int /*<<< orphan*/  enum_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_fprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
save_option_color_attr(FILE *file, int attr)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(attr_map); i++)
		if ((attr & attr_map[i].value) &&
		    !io_fprintf(file, " %s", enum_name(attr_map[i].name)))
			return false;

	return true;
}