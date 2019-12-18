#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_cksum_t ;
struct TYPE_6__ {int /*<<< orphan*/ * labels; } ;
typedef  TYPE_1__ cksum_record_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  avl_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* cksum_record_alloc (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* cksum_record_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static cksum_record_t *
cksum_record_insert(avl_tree_t *tree, zio_cksum_t *cksum, int l)
{
	cksum_record_t *rec;

	rec = cksum_record_lookup(tree, cksum);
	if (rec) {
		rec->labels[l] = B_TRUE;
	} else {
		rec = cksum_record_alloc(cksum, l);
		avl_add(tree, rec);
	}

	return (rec);
}