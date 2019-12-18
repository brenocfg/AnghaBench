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
typedef  int /*<<< orphan*/  opj_t1_t ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_t1_dec_sigpass_mqc_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void opj_t1_dec_sigpass_mqc_64x64_vsc(
    opj_t1_t *t1,
    OPJ_INT32 bpno)
{
    opj_t1_dec_sigpass_mqc_internal(t1, bpno, OPJ_TRUE, 64, 64, 66);
}