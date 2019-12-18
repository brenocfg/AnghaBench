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
typedef  int /*<<< orphan*/  zap_flags_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dnode_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_object_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  zap_create_impl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ **,void*,int /*<<< orphan*/ *) ; 

uint64_t
zap_create_hold(objset_t *os, int normflags, zap_flags_t flags,
    dmu_object_type_t ot, int leaf_blockshift, int indirect_blockshift,
    dmu_object_type_t bonustype, int bonuslen, int dnodesize,
    dnode_t **allocated_dnode, void *tag, dmu_tx_t *tx)
{
	return (zap_create_impl(os, normflags, flags, ot, leaf_blockshift,
	    indirect_blockshift, bonustype, bonuslen, dnodesize,
	    allocated_dnode, tag, tx));
}