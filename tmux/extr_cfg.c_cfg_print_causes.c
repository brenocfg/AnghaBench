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
typedef  size_t u_int ;
struct cmdq_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ ***** cfg_causes ; 
 size_t cfg_ncauses ; 
 int /*<<< orphan*/  cmdq_print (struct cmdq_item*,char*,int /*<<< orphan*/ ****) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *****) ; 

void
cfg_print_causes(struct cmdq_item *item)
{
	u_int	 i;

	for (i = 0; i < cfg_ncauses; i++) {
		cmdq_print(item, "%s", cfg_causes[i]);
		free(cfg_causes[i]);
	}

	free(cfg_causes);
	cfg_causes = NULL;
	cfg_ncauses = 0;
}