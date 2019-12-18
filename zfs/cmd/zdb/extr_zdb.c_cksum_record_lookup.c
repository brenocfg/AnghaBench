#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_cksum_t ;
struct TYPE_5__ {int /*<<< orphan*/  cksum; } ;
typedef  TYPE_1__ cksum_record_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 TYPE_1__* avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static cksum_record_t *
cksum_record_lookup(avl_tree_t *tree, zio_cksum_t *cksum)
{
	cksum_record_t lookup = { .cksum = *cksum };
	avl_index_t where;

	return (avl_find(tree, &lookup, &where));
}