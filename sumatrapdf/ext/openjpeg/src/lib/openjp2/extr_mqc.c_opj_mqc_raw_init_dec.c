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
struct TYPE_4__ {scalar_t__ ct; scalar_t__ c; } ;
typedef  TYPE_1__ opj_mqc_t ;
typedef  int /*<<< orphan*/  OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  opj_mqc_init_dec_common (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void opj_mqc_raw_init_dec(opj_mqc_t *mqc, OPJ_BYTE *bp, OPJ_UINT32 len,
                          OPJ_UINT32 extra_writable_bytes)
{
    opj_mqc_init_dec_common(mqc, bp, len, extra_writable_bytes);
    mqc->c = 0;
    mqc->ct = 0;
}