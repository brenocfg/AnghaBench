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
struct TYPE_4__ {int nChannels; int nSamplesPerSec; int nAvgBytesPerSec; int nBlockAlign; int wBitsPerSample; scalar_t__ cbSize; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_5__ {TYPE_1__* lpWaveFormat; TYPE_1__ wfxRef; } ;
typedef  TYPE_2__ WINE_MCIWAVE ;

/* Variables and functions */
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 

__attribute__((used)) static void WAVE_mciDefaultFmt(WINE_MCIWAVE* wmw)
{
    wmw->lpWaveFormat = &wmw->wfxRef;
    wmw->lpWaveFormat->wFormatTag = WAVE_FORMAT_PCM;
    wmw->lpWaveFormat->nChannels = 1;
    wmw->lpWaveFormat->nSamplesPerSec = 11025;
    wmw->lpWaveFormat->nAvgBytesPerSec = 11025;
    wmw->lpWaveFormat->nBlockAlign = 1;
    wmw->lpWaveFormat->wBitsPerSample = 8;
    wmw->lpWaveFormat->cbSize = 0;
}