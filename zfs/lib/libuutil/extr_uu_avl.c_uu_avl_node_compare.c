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
struct uu_avl_node_compare_info {int (* ac_compare ) (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * ac_found; int /*<<< orphan*/  ac_private; int /*<<< orphan*/  ac_right; } ;

/* Variables and functions */
 int stub1 (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uu_avl_node_compare(const void *l, const void *r)
{
	struct uu_avl_node_compare_info *info =
	    (struct uu_avl_node_compare_info *)l;

	int res = info->ac_compare(r, info->ac_right, info->ac_private);

	if (res == 0) {
		if (info->ac_found == NULL)
			info->ac_found = (void *)r;
		return (-1);
	}
	if (res < 0)
		return (1);
	return (-1);
}