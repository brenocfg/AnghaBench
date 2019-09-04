#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ wFormatTag; } ;
struct TYPE_15__ {int /*<<< orphan*/  SubFormat; TYPE_1__ Format; } ;
typedef  TYPE_5__ WAVEFORMATEXTENSIBLE ;
struct TYPE_16__ {int freq; int writelead; int max_buffer_len; int freqAcc; int freqAccNext; int freqneeded; int tmp_buffer_len; int buflen; int /*<<< orphan*/  sec_mixpos; int /*<<< orphan*/  buf_mixpos; void* resampleinmixer; TYPE_4__* device; int /*<<< orphan*/ * tmp_buffer; TYPE_2__* pwfx; void* convert; } ;
struct TYPE_14__ {int buflen; TYPE_3__* pwfx; } ;
struct TYPE_13__ {int nSamplesPerSec; int nBlockAlign; int wBitsPerSample; scalar_t__ nChannels; } ;
struct TYPE_12__ {int nBlockAlign; int wBitsPerSample; scalar_t__ nChannels; } ;
typedef  TYPE_6__ IDirectSoundBufferImpl ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DSOUND_RecalcFreqAcc (TYPE_6__*) ; 
 int /*<<< orphan*/  DSOUND_secpos_to_bufpos (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FillMemory (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_IEEE_FLOAT ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_6__*) ; 
 void* TRUE ; 
 scalar_t__ WAVE_FORMAT_EXTENSIBLE ; 
 scalar_t__ WAVE_FORMAT_IEEE_FLOAT ; 
 void*** convertbpp ; 
 int ds_snd_shadow_maxsize ; 

void DSOUND_RecalcFormat(IDirectSoundBufferImpl *dsb)
{
	BOOL needremix = TRUE, needresample = (dsb->freq != dsb->device->pwfx->nSamplesPerSec);
	DWORD bAlign = dsb->pwfx->nBlockAlign, pAlign = dsb->device->pwfx->nBlockAlign;
	WAVEFORMATEXTENSIBLE *pwfxe;
	BOOL ieee = FALSE;

	TRACE("(%p)\n",dsb);

	pwfxe = (WAVEFORMATEXTENSIBLE *) dsb->pwfx;

	if ((pwfxe->Format.wFormatTag == WAVE_FORMAT_IEEE_FLOAT) || ((pwfxe->Format.wFormatTag == WAVE_FORMAT_EXTENSIBLE)
	    && (IsEqualGUID(&pwfxe->SubFormat, &KSDATAFORMAT_SUBTYPE_IEEE_FLOAT))))
		ieee = TRUE;

	/* calculate the 10ms write lead */
	dsb->writelead = (dsb->freq / 100) * dsb->pwfx->nBlockAlign;

	if ((dsb->pwfx->wBitsPerSample == dsb->device->pwfx->wBitsPerSample) &&
	    (dsb->pwfx->nChannels == dsb->device->pwfx->nChannels) && !needresample && !ieee)
		needremix = FALSE;
	HeapFree(GetProcessHeap(), 0, dsb->tmp_buffer);
	dsb->tmp_buffer = NULL;
	dsb->max_buffer_len = dsb->freqAcc = dsb->freqAccNext = 0;
	dsb->freqneeded = needresample;

	if (ieee)
		dsb->convert = convertbpp[4][dsb->device->pwfx->wBitsPerSample/8 - 1];
	else
		dsb->convert = convertbpp[dsb->pwfx->wBitsPerSample/8 - 1][dsb->device->pwfx->wBitsPerSample/8 - 1];

	dsb->resampleinmixer = FALSE;

	if (needremix)
	{
		if (needresample)
			DSOUND_RecalcFreqAcc(dsb);
		else
			dsb->tmp_buffer_len = dsb->buflen / bAlign * pAlign;
		dsb->max_buffer_len = dsb->tmp_buffer_len;
		if ((dsb->max_buffer_len <= dsb->device->buflen || dsb->max_buffer_len < ds_snd_shadow_maxsize * 1024 * 1024) && ds_snd_shadow_maxsize >= 0)
			dsb->tmp_buffer = HeapAlloc(GetProcessHeap(), 0, dsb->max_buffer_len);
		if (dsb->tmp_buffer)
			FillMemory(dsb->tmp_buffer, dsb->tmp_buffer_len, dsb->device->pwfx->wBitsPerSample == 8 ? 128 : 0);
		else
			dsb->resampleinmixer = TRUE;
	}
	else dsb->max_buffer_len = dsb->tmp_buffer_len = dsb->buflen;
	dsb->buf_mixpos = DSOUND_secpos_to_bufpos(dsb, dsb->sec_mixpos, 0, NULL);
}