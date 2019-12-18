#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mpcth_t ;
struct TYPE_4__ {int /*<<< orphan*/  apic_address; int /*<<< orphan*/  product_id; int /*<<< orphan*/  oem_id; int /*<<< orphan*/  spec_rev; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAPIC_PADDR ; 
 int /*<<< orphan*/  MPCH_OEMID ; 
 int MPCH_OEMID_LEN ; 
 int /*<<< orphan*/  MPCH_PRODID ; 
 int MPCH_PRODID_LEN ; 
 int /*<<< orphan*/  MPCH_SIG ; 
 int /*<<< orphan*/  MP_SPECREV ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mpt_build_mpch(mpcth_t mpch)
{

	memset(mpch, 0, sizeof(*mpch));
	memcpy(mpch->signature, MPCH_SIG, 4);
	mpch->spec_rev = MP_SPECREV;
	memcpy(mpch->oem_id, MPCH_OEMID, MPCH_OEMID_LEN);
	memcpy(mpch->product_id, MPCH_PRODID, MPCH_PRODID_LEN);
	mpch->apic_address = LAPIC_PADDR;
}