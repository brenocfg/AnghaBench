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
struct TYPE_3__ {int wFormatTag; int nChannels; int wBitsPerSample; int nSamplesPerSec; int nBlockAlign; int nAvgBytesPerSec; scalar_t__ cbSize; } ;
typedef  TYPE_1__ WAVEFORMATEX ;

/* Variables and functions */

void init_format(WAVEFORMATEX* wfx, int format, int rate, int depth,
                 int channels)
{
    wfx->wFormatTag=format;
    wfx->nChannels=channels;
    wfx->wBitsPerSample=depth;
    wfx->nSamplesPerSec=rate;
    wfx->nBlockAlign=wfx->nChannels*wfx->wBitsPerSample/8;
    /* FIXME: Shouldn't this test be if (format!=WAVE_FORMAT_PCM) */
    if (wfx->nBlockAlign==0)
    {
        /* align compressed formats to byte boundary */
        wfx->nBlockAlign=1;
    }
    wfx->nAvgBytesPerSec=wfx->nSamplesPerSec*wfx->nBlockAlign;
    wfx->cbSize=0;
}