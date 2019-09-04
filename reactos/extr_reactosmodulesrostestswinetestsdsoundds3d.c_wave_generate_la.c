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
struct TYPE_3__ {double nSamplesPerSec; int nBlockAlign; int wBitsPerSample; int nChannels; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 double PI ; 
 double sin (double) ; 

char* wave_generate_la(WAVEFORMATEX* wfx, double duration, DWORD* size, BOOL ieee)
{
    int i;
    int nb_samples;
    char* buf;
    char* b;

    nb_samples=(int)(duration*wfx->nSamplesPerSec);
    *size=nb_samples*wfx->nBlockAlign;
    b=buf=HeapAlloc(GetProcessHeap(), 0, *size);
    for (i=0;i<nb_samples;i++) {
        double y=sin(440.0*2*PI*i/wfx->nSamplesPerSec);
        if (wfx->wBitsPerSample==8) {
            unsigned char sample=127.5*(y+1.0);
            *b++=sample;
            if (wfx->nChannels==2)
                *b++=sample;
        } else if (wfx->wBitsPerSample == 16) {
            signed short sample=32767.5*y-0.5;
            b[0]=sample & 0xff;
            b[1]=sample >> 8;
            b+=2;
            if (wfx->nChannels==2) {
                b[0]=sample & 0xff;
                b[1]=sample >> 8;
                b+=2;
            }
        } else if (wfx->wBitsPerSample == 24) {
            signed int sample=8388607.5*y-0.5;
            b[0]=sample & 0xff;
            b[1]=(sample >> 8)&0xff;
            b[2]=sample >> 16;
            b+=3;
            if (wfx->nChannels==2) {
                b[0]=sample & 0xff;
                b[1]=(sample >> 8)&0xff;
                b[2]=sample >> 16;
                b+=3;
            }
        } else if (wfx->wBitsPerSample == 32) {
            if (ieee) {
                float *ptr = (float *) b;
                *ptr = y;

                ptr++;
                b+=4;

                if (wfx->nChannels==2) {
                    *ptr = y;
                    b+=4;
                }
            } else {
                signed int sample=2147483647.5*y-0.5;
                b[0]=sample & 0xff;
                b[1]=(sample >> 8)&0xff;
                b[2]=(sample >> 16)&0xff;
                b[3]=sample >> 24;
                b+=4;
                if (wfx->nChannels==2) {
                    b[0]=sample & 0xff;
                    b[1]=(sample >> 8)&0xff;
                    b[2]=(sample >> 16)&0xff;
                    b[3]=sample >> 24;
                    b+=4;
                }
            }
        }
    }
    return buf;
}