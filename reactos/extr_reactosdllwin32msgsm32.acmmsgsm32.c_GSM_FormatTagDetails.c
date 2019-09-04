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
typedef  char WCHAR ;
struct TYPE_3__ {int dwFormatTagIndex; int dwFormatTag; int cbFormatSize; int /*<<< orphan*/  szFormatTag; void* cStandardFormats; int /*<<< orphan*/  fdwSupport; } ;
typedef  int /*<<< orphan*/  PCMWAVEFORMAT ;
typedef  TYPE_1__* PACMFORMATTAGDETAILSW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  GSM610WAVEFORMAT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACMDRIVERDETAILS_SUPPORTF_CODEC ; 
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
#define  ACM_FORMATTAGDETAILSF_FORMATTAG 132 
#define  ACM_FORMATTAGDETAILSF_INDEX 131 
#define  ACM_FORMATTAGDETAILSF_LARGESTSIZE 130 
 void* ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOTSUPPORTED ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
#define  WAVE_FORMAT_GSM610 129 
#define  WAVE_FORMAT_PCM 128 
 int WAVE_FORMAT_UNKNOWN ; 
 int /*<<< orphan*/  gsm_rates ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static	LRESULT	GSM_FormatTagDetails(PACMFORMATTAGDETAILSW aftd, DWORD dwQuery)
{
    static const WCHAR szPcm[]={'P','C','M',0};
    static const WCHAR szGsm[]={'G','S','M',' ','6','.','1','0',0};

    switch (dwQuery)
    {
    case ACM_FORMATTAGDETAILSF_INDEX:
	if (aftd->dwFormatTagIndex > 1) return ACMERR_NOTPOSSIBLE;
	break;
    case ACM_FORMATTAGDETAILSF_LARGESTSIZE:
	if (aftd->dwFormatTag == WAVE_FORMAT_UNKNOWN)
        {
            aftd->dwFormatTagIndex = 1;
	    break;
	}
	/* fall through */
    case ACM_FORMATTAGDETAILSF_FORMATTAG:
	switch (aftd->dwFormatTag)
        {
	case WAVE_FORMAT_PCM: aftd->dwFormatTagIndex = 0; break;
	case WAVE_FORMAT_GSM610: aftd->dwFormatTagIndex = 1; break;
	default: return ACMERR_NOTPOSSIBLE;
	}
	break;
    default:
	WARN("Unsupported query %08x\n", dwQuery);
	return MMSYSERR_NOTSUPPORTED;
    }

    aftd->fdwSupport = ACMDRIVERDETAILS_SUPPORTF_CODEC;
    switch (aftd->dwFormatTagIndex)
    {
    case 0:
	aftd->dwFormatTag = WAVE_FORMAT_PCM;
	aftd->cbFormatSize = sizeof(PCMWAVEFORMAT);
	aftd->cStandardFormats = ARRAY_SIZE(gsm_rates);
        lstrcpyW(aftd->szFormatTag, szPcm);
        break;
    case 1:
	aftd->dwFormatTag = WAVE_FORMAT_GSM610;
	aftd->cbFormatSize = sizeof(GSM610WAVEFORMAT);
	aftd->cStandardFormats = ARRAY_SIZE(gsm_rates);
        lstrcpyW(aftd->szFormatTag, szGsm);
	break;
    }
    return MMSYSERR_NOERROR;
}