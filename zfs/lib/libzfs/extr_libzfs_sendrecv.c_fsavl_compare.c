#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fn_guid; } ;
typedef  TYPE_1__ fsavl_node_t ;

/* Variables and functions */
 int TREE_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fsavl_compare(const void *arg1, const void *arg2)
{
	const fsavl_node_t *fn1 = (const fsavl_node_t *)arg1;
	const fsavl_node_t *fn2 = (const fsavl_node_t *)arg2;

	return (TREE_CMP(fn1->fn_guid, fn2->fn_guid));
}