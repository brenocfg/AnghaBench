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
 double PI ; 
 scalar_t__ WAVE_FORMAT_EXTENSIBLE ; 
 scalar_t__ WAVE_FORMAT_PCM ; 
 double sin (double) ; 

__attribute__((used)) static char* wave_generate_la(WAVEFORMATEX* wfx, double duration, DWORD* size)
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
        double y=sin(440.0*2*PI*i/wfx->nSamplesPerSec);
        if (wfx->wBitsPerSample==8) {
            unsigned char sample=(unsigned char)((double)127.5*(y+1.0));
            for (j = 0; j < wfx->nChannels; j++)
                *b++=sample;
        } else if (wfx->wBitsPerSample==16) {
            signed short sample=(signed short)((double)32767.5*y-0.5);
            for (j = 0; j < wfx->nChannels; j++) {
                b[0]=sample & 0xff;
                b[1]=sample >> 8;
                b+=2;
            }
        } else if (wfx->wBitsPerSample==24) {
            signed int sample=(signed int)(((double)0x7fffff+0.5)*y-0.5);
            for (j = 0; j < wfx->nChannels; j++) {
                b[0]=sample & 0xff;
                b[1]=(sample >> 8) & 0xff;
                b[2]=(sample >> 16) & 0xff;
                b+=3;
            }
        } else if ((wfx->wBitsPerSample==32) && ((wfx->wFormatTag == WAVE_FORMAT_PCM) ||
            ((wfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE) &&
            IsEqualGUID(&wfex->SubFormat, &KSDATAFORMAT_SUBTYPE_PCM)))) {
            signed int sample=(signed int)(((double)0x7fffffff+0.5)*y-0.5);
            for (j = 0; j < wfx->nChannels; j++) {
                b[0]=sample & 0xff;
                b[1]=(sample >> 8) & 0xff;
                b[2]=(sample >> 16) & 0xff;
                b[3]=(sample >> 24) & 0xff;
                b+=4;
            }
        } else if ((wfx->wBitsPerSample==32) && (wfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE) &&
            IsEqualGUID(&wfex->SubFormat, &KSDATAFORMAT_SUBTYPE_IEEE_FLOAT)) {
            union { float f; char c[4]; } sample;
            sample.f=(float)y;
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