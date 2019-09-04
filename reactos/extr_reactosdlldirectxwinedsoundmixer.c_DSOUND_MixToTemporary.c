#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ resampleinmixer; int buflen; int freqAdjust; TYPE_4__* buffer; int /*<<< orphan*/  sec_mixpos; TYPE_3__* device; int /*<<< orphan*/  freq; int /*<<< orphan*/ * tmp_buffer; TYPE_1__* pwfx; } ;
struct TYPE_12__ {int /*<<< orphan*/ * memory; } ;
struct TYPE_11__ {int tmp_buffer_len; TYPE_2__* pwfx; int /*<<< orphan*/ * tmp_buffer; } ;
struct TYPE_10__ {int nBlockAlign; int /*<<< orphan*/  nSamplesPerSec; } ;
struct TYPE_9__ {int nBlockAlign; } ;
typedef  int INT ;
typedef  TYPE_5__ IDirectSoundBufferImpl ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int DSOUND_FREQSHIFT ; 
 int DSOUND_secpos_to_bufpos (TYPE_5__ const*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cp_fields (TYPE_5__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int) ; 

void DSOUND_MixToTemporary(const IDirectSoundBufferImpl *dsb, DWORD writepos, DWORD len, BOOL inmixer)
{
	INT	size;
	BYTE	*ibp, *obp, *obp_begin;
	INT	iAdvance = dsb->pwfx->nBlockAlign;
	INT	oAdvance = dsb->device->pwfx->nBlockAlign;
	DWORD freqAcc, target_writepos = 0, overshot, maxlen;

	/* We resample only when needed */
	if ((dsb->tmp_buffer && inmixer) || (!dsb->tmp_buffer && !inmixer) || dsb->resampleinmixer != inmixer)
		return;

	assert(writepos + len <= dsb->buflen);
	if (inmixer && writepos + len < dsb->buflen)
		len += dsb->pwfx->nBlockAlign;

	maxlen = DSOUND_secpos_to_bufpos(dsb, len, 0, NULL);

	ibp = dsb->buffer->memory + writepos;
	if (!inmixer)
		obp_begin = dsb->tmp_buffer;
	else if (dsb->device->tmp_buffer_len < maxlen || !dsb->device->tmp_buffer)
	{
		dsb->device->tmp_buffer_len = maxlen;
		if (dsb->device->tmp_buffer)
			dsb->device->tmp_buffer = HeapReAlloc(GetProcessHeap(), 0, dsb->device->tmp_buffer, maxlen);
		else
			dsb->device->tmp_buffer = HeapAlloc(GetProcessHeap(), 0, maxlen);
		obp_begin = dsb->device->tmp_buffer;
	}
	else
		obp_begin = dsb->device->tmp_buffer;

	TRACE("(%p, %p)\n", dsb, ibp);
	size = len / iAdvance;

	/* Check for same sample rate */
	if (dsb->freq == dsb->device->pwfx->nSamplesPerSec) {
		TRACE("(%p) Same sample rate %d = primary %d\n", dsb,
			dsb->freq, dsb->device->pwfx->nSamplesPerSec);
		obp = obp_begin;
		if (!inmixer)
			 obp += writepos/iAdvance*oAdvance;

		cp_fields(dsb, ibp, obp, iAdvance, oAdvance, size, 0, 1 << DSOUND_FREQSHIFT);
		return;
	}

	/* Mix in different sample rates */
	TRACE("(%p) Adjusting frequency: %d -> %d\n", dsb, dsb->freq, dsb->device->pwfx->nSamplesPerSec);

	target_writepos = DSOUND_secpos_to_bufpos(dsb, writepos, dsb->sec_mixpos, &freqAcc);
	overshot = freqAcc >> DSOUND_FREQSHIFT;
	if (overshot)
	{
		if (overshot >= size)
			return;
		size -= overshot;
		writepos += overshot * iAdvance;
		if (writepos >= dsb->buflen)
			return;
		ibp = dsb->buffer->memory + writepos;
		freqAcc &= (1 << DSOUND_FREQSHIFT) - 1;
		TRACE("Overshot: %d, freqAcc: %04x\n", overshot, freqAcc);
	}

	if (!inmixer)
		obp = obp_begin + target_writepos;
	else obp = obp_begin;

	/* FIXME: Small problem here when we're overwriting buf_mixpos, it then STILL uses old freqAcc, not sure if it matters or not */
	cp_fields(dsb, ibp, obp, iAdvance, oAdvance, size, freqAcc, dsb->freqAdjust);
}