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
struct TYPE_4__ {int a; int* bp; int ct; int* start; scalar_t__ end_of_byte_stream_counter; scalar_t__ c; } ;
typedef  TYPE_1__ opj_mqc_t ;
typedef  int OPJ_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  opj_mqc_setcurctx (TYPE_1__*,int /*<<< orphan*/ ) ; 

void opj_mqc_init_enc(opj_mqc_t *mqc, OPJ_BYTE *bp)
{
    /* To avoid the curctx pointer to be dangling, but not strictly */
    /* required as the current context is always set before encoding */
    opj_mqc_setcurctx(mqc, 0);

    /* As specified in Figure C.10 - Initialization of the encoder */
    /* (C.2.8 Initialization of the encoder (INITENC)) */
    mqc->a = 0x8000;
    mqc->c = 0;
    /* Yes, we point before the start of the buffer, but this is safe */
    /* given opj_tcd_code_block_enc_allocate_data() */
    mqc->bp = bp - 1;
    mqc->ct = 12;
    /* At this point we should test *(mqc->bp) against 0xFF, but this is not */
    /* necessary, as this is only used at the beginning of the code block */
    /* and our initial fake byte is set at 0 */
    assert(*(mqc->bp) != 0xff);

    mqc->start = bp;
    mqc->end_of_byte_stream_counter = 0;
}