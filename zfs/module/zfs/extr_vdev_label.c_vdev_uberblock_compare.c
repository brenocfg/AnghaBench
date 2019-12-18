#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int ub_txg; unsigned int ub_timestamp; } ;
typedef  TYPE_1__ uberblock_t ;

/* Variables and functions */
 unsigned int MMP_SEQ (TYPE_1__ const*) ; 
 scalar_t__ MMP_SEQ_VALID (TYPE_1__ const*) ; 
 scalar_t__ MMP_VALID (TYPE_1__ const*) ; 
 int TREE_CMP (unsigned int,unsigned int) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int
vdev_uberblock_compare(const uberblock_t *ub1, const uberblock_t *ub2)
{
	int cmp = TREE_CMP(ub1->ub_txg, ub2->ub_txg);

	if (likely(cmp))
		return (cmp);

	cmp = TREE_CMP(ub1->ub_timestamp, ub2->ub_timestamp);
	if (likely(cmp))
		return (cmp);

	/*
	 * If MMP_VALID(ub) && MMP_SEQ_VALID(ub) then the host has an MMP-aware
	 * ZFS, e.g. zfsonlinux >= 0.7.
	 *
	 * If one ub has MMP and the other does not, they were written by
	 * different hosts, which matters for MMP.  So we treat no MMP/no SEQ as
	 * a 0 value.
	 *
	 * Since timestamp and txg are the same if we get this far, either is
	 * acceptable for importing the pool.
	 */
	unsigned int seq1 = 0;
	unsigned int seq2 = 0;

	if (MMP_VALID(ub1) && MMP_SEQ_VALID(ub1))
		seq1 = MMP_SEQ(ub1);

	if (MMP_VALID(ub2) && MMP_SEQ_VALID(ub2))
		seq2 = MMP_SEQ(ub2);

	return (TREE_CMP(seq1, seq2));
}