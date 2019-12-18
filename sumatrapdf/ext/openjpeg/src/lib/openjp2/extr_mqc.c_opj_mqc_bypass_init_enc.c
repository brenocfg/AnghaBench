#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* bp; int* start; int /*<<< orphan*/  ct; scalar_t__ c; } ;
typedef  TYPE_1__ opj_mqc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BYPASS_CT_INIT ; 
 int /*<<< orphan*/  assert (int) ; 

void opj_mqc_bypass_init_enc(opj_mqc_t *mqc)
{
    /* This function is normally called after at least one opj_mqc_flush() */
    /* which will have advance mqc->bp by at least 2 bytes beyond its */
    /* initial position */
    assert(mqc->bp >= mqc->start);
    mqc->c = 0;
    /* in theory we should initialize to 8, but use this special value */
    /* as a hint that opj_mqc_bypass_enc() has never been called, so */
    /* as to avoid the 0xff 0x7f elimination trick in opj_mqc_bypass_flush_enc() */
    /* to trigger when we don't have output any bit during this bypass sequence */
    /* Any value > 8 will do */
    mqc->ct = BYPASS_CT_INIT;
    /* Given that we are called after opj_mqc_flush(), the previous byte */
    /* cannot be 0xff. */
    assert(mqc->bp[-1] != 0xff);
}