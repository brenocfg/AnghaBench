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
struct TYPE_4__ {int /*<<< orphan*/  tmp_buffer_len; int /*<<< orphan*/  freqAccNext; int /*<<< orphan*/  buflen; int /*<<< orphan*/  freqAcc; int /*<<< orphan*/  freqneeded; } ;
typedef  TYPE_1__ IDirectSoundBufferImpl ;

/* Variables and functions */
 int /*<<< orphan*/  DSOUND_secpos_to_bufpos (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DSOUND_RecalcFreqAcc(IDirectSoundBufferImpl *dsb)
{
	if (!dsb->freqneeded) return;
	dsb->freqAcc = dsb->freqAccNext;
	dsb->tmp_buffer_len = DSOUND_secpos_to_bufpos(dsb, dsb->buflen, 0, &dsb->freqAccNext);
	TRACE("New freqadjust: %04x, new buflen: %d\n", dsb->freqAccNext, dsb->tmp_buffer_len);
}