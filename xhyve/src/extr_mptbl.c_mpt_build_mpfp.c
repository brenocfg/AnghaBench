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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* mpfps_t ;
struct TYPE_5__ {int length; int /*<<< orphan*/  checksum; int /*<<< orphan*/  spec_rev; scalar_t__ pap; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPFP_SIG ; 
 int /*<<< orphan*/  MP_SPECREV ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt_compute_checksum (TYPE_1__*,int) ; 

__attribute__((used)) static void
mpt_build_mpfp(mpfps_t mpfp, uint64_t gpa)
{
	memset(mpfp, 0, sizeof(*mpfp));
	memcpy(mpfp->signature, MPFP_SIG, 4);
	mpfp->pap = (uint32_t) (gpa + sizeof(*mpfp));
	mpfp->length = 1;
	mpfp->spec_rev = MP_SPECREV;
	mpfp->checksum = mpt_compute_checksum(mpfp, sizeof(*mpfp));
}