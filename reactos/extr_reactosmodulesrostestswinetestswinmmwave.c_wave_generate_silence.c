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
struct TYPE_4__ {int /*<<< orphan*/  SubFormat; } ;
typedef  TYPE_1__ WAVEFORMATEXTENSIBLE ;
struct TYPE_5__ {double nSamplesPerSec; int nBlockAlign; int wBitsPerSample; int nChannels; scalar_t__ wFormatTag; } ;
typedef  TYPE_2__ WAVEFORMATEX ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_IEEE_FLOAT ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_PCM ; 
 scalar_t__ WAVE_FORMAT_EXTENSIBLE ; 
 scalar_t__ WAVE_FORMAT_PCM ; 

__attribute__((used)) static char* wave_generate_silence(WAVEFORMATEX* wfx, double duration, DWORD* size)
{
    int i,j;
    int nb_samples;
    char* buf;
    char* b;
    WAVEFORMATEXTENSIBLE *wfex = (WAVEFORMATEXTENSIBLE*)wfx;

    nb_samples=(int)(duration*wfx->nSamplesPerSec);
    *size=nb_samples*wfx->nBlockAlign;
    b=buf=HeapAlloc(GetProcessHeap(), 0, *size);
    for (i=0;i<nb_samples;i++) {
        if (wfx->wBitsPerSample==8) {
            for (j = 0; j < wfx->nChannels; j++)
                *b++=128;
        } else if (wfx->wBitsPerSample==16) {
            for (j = 0; j < wfx->nChannels; j++) {
                b[0]=0;
                b[1]=0;
                b+=2;
            }
        } else if (wfx->wBitsPerSample==24) {
            for (j = 0; j < wfx->nChannels; j++) {
                b[0]=0;
                b[1]=0;
                b[2]=0;
                b+=3;
            }
        } else if ((wfx->wBitsPerSample==32) && ((wfx->wFormatTag == WAVE_FORMAT_PCM) ||
            ((wfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE) &&
            IsEqualGUID(&wfex->SubFormat, &KSDATAFORMAT_SUBTYPE_PCM)))) {
            for (j = 0; j < wfx->nChannels; j++) {
                b[0]=0;
                b[1]=0;
                b[2]=0;
                b[3]=0;
                b+=4;
            }
        } else if ((wfx->wBitsPerSample==32) && (wfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE) &&
            IsEqualGUID(&wfex->SubFormat, &KSDATAFORMAT_SUBTYPE_IEEE_FLOAT)) {
            union { float f; char c[4]; } sample;
            sample.f=0;
            for (j = 0; j < wfx->nChannels; j++) {
                b[0]=sample.c[0];
                b[1]=sample.c[1];
                b[2]=sample.c[2];
                b[3]=sample.c[3];
                b+=4;
            }
        }
    }
    return buf;
}