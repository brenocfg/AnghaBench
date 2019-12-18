#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_3__ {int wBitsPerSample; scalar_t__ wFormatTag; int nChannels; int nSamplesPerSec; } ;
struct TYPE_4__ {TYPE_1__ Format; int /*<<< orphan*/  SubFormat; } ;
typedef  TYPE_2__* PWAVEFORMATEXTENSIBLE ;
typedef  int /*<<< orphan*/  PWAVEFORMATEX ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int AUDCLNT_BUFFERFLAGS_SILENT ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_IEEE_FLOAT ; 
 int PI ; 
 scalar_t__ WAVE_FORMAT_EXTENSIBLE ; 
 scalar_t__ floor (double) ; 
 double sin (int) ; 
 int /*<<< orphan*/  winetest_interactive ; 

__attribute__((used)) static DWORD wave_generate_tone(PWAVEFORMATEX pwfx, BYTE* data, UINT32 frames)
{
    static double phase = 0.; /* normalized to unit, not 2*PI */
    PWAVEFORMATEXTENSIBLE wfxe = (PWAVEFORMATEXTENSIBLE)pwfx;
    DWORD cn, i;
    double delta, y;

    if(!winetest_interactive)
        return AUDCLNT_BUFFERFLAGS_SILENT;
    if(wfxe->Format.wBitsPerSample != ((wfxe->Format.wFormatTag == WAVE_FORMAT_EXTENSIBLE &&
       IsEqualGUID(&wfxe->SubFormat, &KSDATAFORMAT_SUBTYPE_IEEE_FLOAT)) ? 8 * sizeof(float) : 16))
        return AUDCLNT_BUFFERFLAGS_SILENT;

    for(delta = phase, cn = 0; cn < wfxe->Format.nChannels;
        delta += .5/wfxe->Format.nChannels, cn++){
        for(i = 0; i < frames; i++){
            y = sin(2*PI*(440.* i / wfxe->Format.nSamplesPerSec + delta));
            /* assume alignment is granted */
            if(wfxe->Format.wBitsPerSample == 16)
                ((short*)data)[cn+i*wfxe->Format.nChannels] = y * 32767.9;
            else
                ((float*)data)[cn+i*wfxe->Format.nChannels] = y;
        }
    }
    phase += 440.* frames / wfxe->Format.nSamplesPerSec;
    phase -= floor(phase);
    return 0;
}