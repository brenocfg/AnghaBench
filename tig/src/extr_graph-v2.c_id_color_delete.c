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
struct id_color {struct id_color* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct id_color*) ; 

__attribute__((used)) static void
id_color_delete(struct id_color *node)
{
	free(node->id);
	free(node);
}