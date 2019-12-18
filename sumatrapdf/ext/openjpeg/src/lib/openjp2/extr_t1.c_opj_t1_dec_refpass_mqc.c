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
struct TYPE_5__ {int w; int h; } ;
typedef  TYPE_1__ opj_t1_t ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  opj_t1_dec_refpass_mqc_64x64 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_t1_dec_refpass_mqc_generic (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opj_t1_dec_refpass_mqc(
    opj_t1_t *t1,
    OPJ_INT32 bpno)
{
    if (t1->w == 64 && t1->h == 64) {
        opj_t1_dec_refpass_mqc_64x64(t1, bpno);
    } else {
        opj_t1_dec_refpass_mqc_generic(t1, bpno);
    }
}