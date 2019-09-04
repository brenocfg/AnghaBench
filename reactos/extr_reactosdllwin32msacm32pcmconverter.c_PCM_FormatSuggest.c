#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nChannels; int nSamplesPerSec; int wBitsPerSample; scalar_t__ wFormatTag; int nBlockAlign; int nAvgBytesPerSec; } ;
struct TYPE_5__ {int cbwfxSrc; int cbwfxDst; int fdwSuggest; TYPE_3__* pwfxDst; TYPE_3__* pwfxSrc; } ;
typedef  int /*<<< orphan*/  PCMWAVEFORMAT ;
typedef  TYPE_1__* PACMDRVFORMATSUGGEST ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
 int ACM_FORMATSUGGESTF_NCHANNELS ; 
 int ACM_FORMATSUGGESTF_NSAMPLESPERSEC ; 
 int ACM_FORMATSUGGESTF_WBITSPERSAMPLE ; 
 int ACM_FORMATSUGGESTF_WFORMATTAG ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int PCM_GetFormatIndex (TYPE_3__*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 scalar_t__ WAVE_FORMAT_PCM ; 

__attribute__((used)) static	LRESULT	PCM_FormatSuggest(PACMDRVFORMATSUGGEST adfs)
{
    TRACE("(%p)\n", adfs);

    /* some tests ... */
    if (adfs->cbwfxSrc < sizeof(PCMWAVEFORMAT) ||
        adfs->cbwfxDst < sizeof(PCMWAVEFORMAT) ||
        PCM_GetFormatIndex(adfs->pwfxSrc) == 0xFFFFFFFF) {
            WARN("not possible\n");
            return ACMERR_NOTPOSSIBLE;
    }

    /* is no suggestion for destination, then copy source value */
    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_NCHANNELS)) {
        adfs->pwfxDst->nChannels = adfs->pwfxSrc->nChannels;
    }
    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_NSAMPLESPERSEC)) {
        adfs->pwfxDst->nSamplesPerSec = adfs->pwfxSrc->nSamplesPerSec;
    }
    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_WBITSPERSAMPLE)) {
        adfs->pwfxDst->wBitsPerSample = adfs->pwfxSrc->wBitsPerSample;
    }
    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_WFORMATTAG)) {
        if (adfs->pwfxSrc->wFormatTag != WAVE_FORMAT_PCM) {
            WARN("source format 0x%x not supported\n", adfs->pwfxSrc->wFormatTag);
            return ACMERR_NOTPOSSIBLE;
        }
        adfs->pwfxDst->wFormatTag = adfs->pwfxSrc->wFormatTag;
    } else {
        if (adfs->pwfxDst->wFormatTag != WAVE_FORMAT_PCM) {
            WARN("destination format 0x%x not supported\n", adfs->pwfxDst->wFormatTag);
            return ACMERR_NOTPOSSIBLE;
        }
    }
    /* check if result is ok */
    if (PCM_GetFormatIndex(adfs->pwfxDst) == 0xFFFFFFFF) {
        WARN("not possible\n");
        return ACMERR_NOTPOSSIBLE;
    }

    /* recompute other values */
    adfs->pwfxDst->nBlockAlign = (adfs->pwfxDst->nChannels * adfs->pwfxDst->wBitsPerSample) / 8;
    adfs->pwfxDst->nAvgBytesPerSec = adfs->pwfxDst->nSamplesPerSec * adfs->pwfxDst->nBlockAlign;

    return MMSYSERR_NOERROR;
}