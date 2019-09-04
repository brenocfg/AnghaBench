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
struct sway_workspace {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 int strtol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sort_workspace_cmp_qsort(const void *_a, const void *_b) {
	struct sway_workspace *a = *(void **)_a;
	struct sway_workspace *b = *(void **)_b;

	if (isdigit(a->name[0]) && isdigit(b->name[0])) {
		int a_num = strtol(a->name, NULL, 10);
		int b_num = strtol(b->name, NULL, 10);
		return (a_num < b_num) ? -1 : (a_num > b_num);
	} else if (isdigit(a->name[0])) {
		return -1;
	} else if (isdigit(b->name[0])) {
		return 1;
	}
	return 0;
}