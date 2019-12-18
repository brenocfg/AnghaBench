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
struct TYPE_4__ {scalar_t__ w; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ opj_t1_t ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_t1_dec_clnpass_internal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void opj_t1_dec_clnpass_generic_vsc(
    opj_t1_t *t1,
    OPJ_INT32 bpno)
{
    opj_t1_dec_clnpass_internal(t1, bpno, OPJ_TRUE, t1->w, t1->h,
                                t1->w + 2U);
}