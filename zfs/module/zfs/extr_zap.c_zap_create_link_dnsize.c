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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_object_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_add (int /*<<< orphan*/ *,scalar_t__,char const*,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zap_create_dnsize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

uint64_t
zap_create_link_dnsize(objset_t *os, dmu_object_type_t ot, uint64_t parent_obj,
    const char *name, int dnodesize, dmu_tx_t *tx)
{
	uint64_t new_obj;

	new_obj = zap_create_dnsize(os, ot, DMU_OT_NONE, 0, dnodesize, tx);
	VERIFY(new_obj != 0);
	VERIFY0(zap_add(os, parent_obj, name, sizeof (uint64_t), 1, &new_obj,
	    tx));

	return (new_obj);
}