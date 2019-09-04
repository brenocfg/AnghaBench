#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ wFormatTag; scalar_t__ nSamplesPerSec; unsigned int nChannels; int wBitsPerSample; unsigned int nBlockAlign; } ;
struct TYPE_12__ {void* convert; } ;
struct TYPE_11__ {unsigned int wSamplesPerBlock; } ;
struct TYPE_10__ {int fdwOpen; long dwDriver; TYPE_9__* pwfxSrc; TYPE_9__* pwfxDst; } ;
typedef  TYPE_1__* PACMDRVSTREAMINSTANCE ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__* LPIMAADPCMWAVEFORMAT ;
typedef  long DWORD_PTR ;
typedef  TYPE_3__ AcmAdpcmData ;

/* Variables and functions */
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
 int ACM_STREAMOPENF_ASYNC ; 
 int ADPCM_GetFormatIndex (TYPE_9__*) ; 
 int /*<<< orphan*/  ADPCM_Reset (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOMEM ; 
 int /*<<< orphan*/  MMSYSERR_NOTSUPPORTED ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int) ; 
 scalar_t__ WAVE_FORMAT_IMA_ADPCM ; 
 scalar_t__ WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  assert (int) ; 
 void* cvtMM16imaK ; 
 void* cvtMMimaK ; 
 void* cvtSS16imaK ; 
 void* cvtSSima16K ; 

__attribute__((used)) static	LRESULT	ADPCM_StreamOpen(PACMDRVSTREAMINSTANCE adsi)
{
    AcmAdpcmData*	aad;
    unsigned            nspb;

    assert(!(adsi->fdwOpen & ACM_STREAMOPENF_ASYNC));

    if (ADPCM_GetFormatIndex(adsi->pwfxSrc) == 0xFFFFFFFF ||
	ADPCM_GetFormatIndex(adsi->pwfxDst) == 0xFFFFFFFF)
	return ACMERR_NOTPOSSIBLE;

    aad = HeapAlloc(GetProcessHeap(), 0, sizeof(AcmAdpcmData));
    if (aad == 0) return MMSYSERR_NOMEM;

    adsi->dwDriver = (DWORD_PTR)aad;

    if (adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_PCM &&
	adsi->pwfxDst->wFormatTag == WAVE_FORMAT_PCM)
    {
	goto theEnd;
    }
    else if (adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_IMA_ADPCM &&
             adsi->pwfxDst->wFormatTag == WAVE_FORMAT_PCM)
    {
        /* resampling or mono <=> stereo not available
         * ADPCM algo only define 16 bit per sample output
         * (The API seems to still allow 8 bit per sample output)
         */
        if (adsi->pwfxSrc->nSamplesPerSec != adsi->pwfxDst->nSamplesPerSec ||
            adsi->pwfxSrc->nChannels != adsi->pwfxDst->nChannels ||
            (adsi->pwfxDst->wBitsPerSample != 16 && adsi->pwfxDst->wBitsPerSample != 8))
            goto theEnd;

        nspb = ((LPIMAADPCMWAVEFORMAT)adsi->pwfxSrc)->wSamplesPerBlock;
        TRACE("spb=%u\n", nspb);

        /* we check that in a block, after the header, samples are present on
         * 4-sample packet pattern
         * we also check that the block alignment is bigger than the expected size
         */
        if (((nspb - 1) & 3) != 0) goto theEnd;
        if ((((nspb - 1) / 2) + 4) * adsi->pwfxSrc->nChannels < adsi->pwfxSrc->nBlockAlign)
            goto theEnd;

        /* adpcm decoding... */
        if (adsi->pwfxDst->wBitsPerSample == 16 && adsi->pwfxDst->nChannels == 2)
            aad->convert = cvtSSima16K;
        if (adsi->pwfxDst->wBitsPerSample == 16 && adsi->pwfxDst->nChannels == 1)
            aad->convert = cvtMMimaK;
        if (adsi->pwfxDst->wBitsPerSample == 8 && adsi->pwfxDst->nChannels == 1)
            aad->convert = cvtMMimaK;
        /* FIXME: Stereo support for 8bit samples*/
        if (adsi->pwfxDst->wBitsPerSample == 8 && adsi->pwfxDst->nChannels == 2)
            goto theEnd;
    }
    else if (adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_PCM &&
             adsi->pwfxDst->wFormatTag == WAVE_FORMAT_IMA_ADPCM)
    {
	if (adsi->pwfxSrc->nSamplesPerSec != adsi->pwfxDst->nSamplesPerSec ||
	    adsi->pwfxSrc->nChannels != adsi->pwfxDst->nChannels ||
            adsi->pwfxSrc->wBitsPerSample != 16)
	    goto theEnd;

        nspb = ((LPIMAADPCMWAVEFORMAT)adsi->pwfxDst)->wSamplesPerBlock;
        TRACE("spb=%u\n", nspb);

        /* we check that in a block, after the header, samples are present on
         * 4-sample packet pattern
         * we also check that the block alignment is bigger than the expected size
         */
        if (((nspb - 1) & 3) != 0) goto theEnd;
        if ((((nspb - 1) / 2) + 4) * adsi->pwfxDst->nChannels < adsi->pwfxDst->nBlockAlign)
            goto theEnd;

	/* adpcm coding... */
	if (adsi->pwfxSrc->wBitsPerSample == 16 && adsi->pwfxSrc->nChannels == 2)
	    aad->convert = cvtSS16imaK;
	if (adsi->pwfxSrc->wBitsPerSample == 16 && adsi->pwfxSrc->nChannels == 1)
	    aad->convert = cvtMM16imaK;
    }
    else goto theEnd;
    ADPCM_Reset(adsi, aad);

    return MMSYSERR_NOERROR;

 theEnd:
    HeapFree(GetProcessHeap(), 0, aad);
    adsi->dwDriver = 0L;
    return MMSYSERR_NOTSUPPORTED;
}