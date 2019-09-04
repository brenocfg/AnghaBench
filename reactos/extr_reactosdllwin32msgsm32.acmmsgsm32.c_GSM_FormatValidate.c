#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_4__ {int nChannels; int wFormatTag; int wBitsPerSample; int nBlockAlign; int nAvgBytesPerSec; int nSamplesPerSec; int cbSize; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
struct TYPE_5__ {int wSamplesPerBlock; } ;
typedef  TYPE_2__ GSM610WAVEFORMAT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int,...) ; 
#define  WAVE_FORMAT_GSM610 129 
#define  WAVE_FORMAT_PCM 128 

__attribute__((used)) static BOOL GSM_FormatValidate(const WAVEFORMATEX *wfx)
{
    if (wfx->nChannels != 1)
        return FALSE;

    switch (wfx->wFormatTag)
    {
    case WAVE_FORMAT_PCM:
        if (wfx->wBitsPerSample != 16)
        {
            WARN("PCM wBitsPerSample %u\n", wfx->wBitsPerSample);
            return FALSE;
        }
        if (wfx->nBlockAlign != 2)
        {
            WARN("PCM nBlockAlign %u\n", wfx->nBlockAlign);
            return FALSE;
        }
        if (wfx->nAvgBytesPerSec != wfx->nBlockAlign * wfx->nSamplesPerSec)
        {
            WARN("PCM nAvgBytesPerSec %u/%u\n",
                 wfx->nAvgBytesPerSec,
                 wfx->nBlockAlign * wfx->nSamplesPerSec);
            return FALSE;
        }
        return TRUE;
    case WAVE_FORMAT_GSM610:
        if (wfx->cbSize < sizeof(WORD))
        {
            WARN("GSM cbSize %u\n", wfx->cbSize);
            return FALSE;
        }
        if (wfx->wBitsPerSample != 0)
        {
            WARN("GSM wBitsPerSample %u\n", wfx->wBitsPerSample);
            return FALSE;
        }
        if (wfx->nBlockAlign != 65)
        {
            WARN("GSM nBlockAlign %u\n", wfx->nBlockAlign);
            return FALSE;
        }
        if (((const GSM610WAVEFORMAT*)wfx)->wSamplesPerBlock != 320)
        {
            WARN("GSM wSamplesPerBlock %u\n",
                 ((const GSM610WAVEFORMAT*)wfx)->wSamplesPerBlock);
            return FALSE;
        }
        if (wfx->nAvgBytesPerSec != wfx->nSamplesPerSec * 65 / 320)
        {
            WARN("GSM nAvgBytesPerSec %d / %d\n",
                 wfx->nAvgBytesPerSec, wfx->nSamplesPerSec * 65 / 320);
            return FALSE;
        }
        return TRUE;
    default:
        return FALSE;
    }
    return FALSE;
}