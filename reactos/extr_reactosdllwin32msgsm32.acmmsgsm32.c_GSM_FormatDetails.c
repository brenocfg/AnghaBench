#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_7__ {int wFormatTag; int nChannels; int nSamplesPerSec; int wBitsPerSample; int nBlockAlign; int nAvgBytesPerSec; int cbSize; } ;
struct TYPE_6__ {int wSamplesPerBlock; } ;
struct TYPE_5__ {int dwFormatTag; size_t dwFormatIndex; scalar_t__* szFormat; int /*<<< orphan*/  fdwSupport; TYPE_3__* pwfx; } ;
typedef  TYPE_1__* PACMFORMATDETAILSW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__ GSM610WAVEFORMAT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACMDRIVERDETAILS_SUPPORTF_CODEC ; 
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
#define  ACM_FORMATDETAILSF_FORMAT 131 
#define  ACM_FORMATDETAILSF_INDEX 130 
 size_t ARRAY_SIZE (void**) ; 
 int /*<<< orphan*/  GSM_FormatValidate (TYPE_3__*) ; 
 int /*<<< orphan*/  MMSYSERR_INVALPARAM ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOTSUPPORTED ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
#define  WAVE_FORMAT_GSM610 129 
#define  WAVE_FORMAT_PCM 128 
 void** gsm_rates ; 

__attribute__((used)) static	LRESULT	GSM_FormatDetails(PACMFORMATDETAILSW afd, DWORD dwQuery)
{
    switch (dwQuery)
    {
    case ACM_FORMATDETAILSF_FORMAT:
	if (!GSM_FormatValidate(afd->pwfx)) return ACMERR_NOTPOSSIBLE;
	break;
    case ACM_FORMATDETAILSF_INDEX:
	afd->pwfx->wFormatTag = afd->dwFormatTag;
	switch (afd->dwFormatTag)
        {
	case WAVE_FORMAT_PCM:
	    if (afd->dwFormatIndex >= ARRAY_SIZE(gsm_rates)) return ACMERR_NOTPOSSIBLE;
	    afd->pwfx->nChannels = 1;
	    afd->pwfx->nSamplesPerSec = gsm_rates[afd->dwFormatIndex];
	    afd->pwfx->wBitsPerSample = 16;
	    afd->pwfx->nBlockAlign = 2;
	    afd->pwfx->nAvgBytesPerSec = afd->pwfx->nSamplesPerSec * afd->pwfx->nBlockAlign;
	    break;
	case WAVE_FORMAT_GSM610:
	    if (afd->dwFormatIndex >= ARRAY_SIZE(gsm_rates)) return ACMERR_NOTPOSSIBLE;
	    afd->pwfx->nChannels = 1;
	    afd->pwfx->nSamplesPerSec = gsm_rates[afd->dwFormatIndex];
	    afd->pwfx->wBitsPerSample = 0;
	    afd->pwfx->nBlockAlign = 65;
            afd->pwfx->nAvgBytesPerSec = afd->pwfx->nSamplesPerSec * 65 / 320;
            afd->pwfx->cbSize = sizeof(WORD);
            ((GSM610WAVEFORMAT*)afd->pwfx)->wSamplesPerBlock = 320;
	    break;
	default:
            WARN("Unsupported tag %08x\n", afd->dwFormatTag);
	    return MMSYSERR_INVALPARAM;
	}
	break;
    default:
	WARN("Unsupported query %08x\n", dwQuery);
	return MMSYSERR_NOTSUPPORTED;
    }
    afd->fdwSupport = ACMDRIVERDETAILS_SUPPORTF_CODEC;
    afd->szFormat[0] = 0; /* let MSACM format this for us... */

    return MMSYSERR_NOERROR;
}