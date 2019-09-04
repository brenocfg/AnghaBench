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
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
struct TYPE_3__ {int dwFormatTagIndex; int dwFormatTag; int cbFormatSize; int /*<<< orphan*/  szFormatTag; void* cStandardFormats; int /*<<< orphan*/  fdwSupport; } ;
typedef  int /*<<< orphan*/  PCMWAVEFORMAT ;
typedef  TYPE_1__* PACMFORMATTAGDETAILSW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACMDRIVERDETAILS_SUPPORTF_CODEC ; 
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
#define  ACM_FORMATTAGDETAILSF_FORMATTAG 133 
#define  ACM_FORMATTAGDETAILSF_INDEX 132 
#define  ACM_FORMATTAGDETAILSF_LARGESTSIZE 131 
 int /*<<< orphan*/  ALaw_Formats ; 
 void* ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOTSUPPORTED ; 
 int /*<<< orphan*/  PCM_Formats ; 
 int /*<<< orphan*/  ULaw_Formats ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
#define  WAVE_FORMAT_ALAW 130 
#define  WAVE_FORMAT_MULAW 129 
#define  WAVE_FORMAT_PCM 128 
 int WAVE_FORMAT_UNKNOWN ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static	LRESULT	G711_FormatTagDetails(PACMFORMATTAGDETAILSW aftd, DWORD dwQuery)
{
    static const WCHAR szPcm[]={'P','C','M',0};
    static const WCHAR szALaw[]={'A','-','L','a','w',0};
    static const WCHAR szULaw[]={'U','-','L','a','w',0};

    switch (dwQuery)
    {
    case ACM_FORMATTAGDETAILSF_INDEX:
	if (aftd->dwFormatTagIndex >= 3) return ACMERR_NOTPOSSIBLE;
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
	case WAVE_FORMAT_PCM:	aftd->dwFormatTagIndex = 0; break;
	case WAVE_FORMAT_ALAW:  aftd->dwFormatTagIndex = 1; break;
	case WAVE_FORMAT_MULAW: aftd->dwFormatTagIndex = 2; break;
	default:		return ACMERR_NOTPOSSIBLE;
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
	aftd->cStandardFormats = ARRAY_SIZE(PCM_Formats);
        lstrcpyW(aftd->szFormatTag, szPcm);
        break;
    case 1:
	aftd->dwFormatTag = WAVE_FORMAT_ALAW;
	aftd->cbFormatSize = sizeof(WAVEFORMATEX);
	aftd->cStandardFormats = ARRAY_SIZE(ALaw_Formats);
        lstrcpyW(aftd->szFormatTag, szALaw);
	break;
    case 2:
	aftd->dwFormatTag = WAVE_FORMAT_MULAW;
	aftd->cbFormatSize = sizeof(WAVEFORMATEX);
	aftd->cStandardFormats = ARRAY_SIZE(ULaw_Formats);
        lstrcpyW(aftd->szFormatTag, szULaw);
	break;
    }
    return MMSYSERR_NOERROR;
}