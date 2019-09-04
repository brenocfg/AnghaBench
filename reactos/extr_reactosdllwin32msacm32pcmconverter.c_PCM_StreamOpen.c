#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  cvtKeepRate; int /*<<< orphan*/  cvtChangeRate; } ;
struct TYPE_14__ {TYPE_1__ cvt; } ;
struct TYPE_13__ {int fdwOpen; scalar_t__ fdwDriver; scalar_t__ dwDriver; TYPE_3__* pwfxDst; TYPE_2__* pwfxSrc; } ;
struct TYPE_12__ {int wBitsPerSample; int nBlockAlign; int nChannels; scalar_t__ nSamplesPerSec; } ;
struct TYPE_11__ {int wBitsPerSample; int nBlockAlign; int nChannels; scalar_t__ nSamplesPerSec; } ;
typedef  TYPE_4__* PACMDRVSTREAMINSTANCE ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ DWORD_PTR ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_5__ AcmPcmData ;

/* Variables and functions */
 int ACM_STREAMOPENF_ASYNC ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_5__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOMEM ; 
 int /*<<< orphan*/  MMSYSERR_NOTSUPPORTED ; 
 int /*<<< orphan*/ * PCM_ConvertChangeRate ; 
 int /*<<< orphan*/ * PCM_ConvertKeepRate ; 
 scalar_t__ PCM_RESAMPLE ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static	LRESULT	PCM_StreamOpen(PACMDRVSTREAMINSTANCE adsi)
{
    AcmPcmData* apd;
    int idx;
    DWORD flags;

    TRACE("(%p)\n", adsi);

    assert(!(adsi->fdwOpen & ACM_STREAMOPENF_ASYNC));

    switch(adsi->pwfxSrc->wBitsPerSample){
    case 8:
        idx = 0;
        break;
    case 16:
        idx = 12;
        break;
    case 24:
        if (adsi->pwfxSrc->nBlockAlign != 3 * adsi->pwfxSrc->nChannels) {
            FIXME("Source: 24-bit samples must be packed\n");
            return MMSYSERR_NOTSUPPORTED;
        }
        idx = 24;
        break;
    default:
        FIXME("Unsupported source bit depth: %u\n", adsi->pwfxSrc->wBitsPerSample);
        return MMSYSERR_NOTSUPPORTED;
    }

    switch(adsi->pwfxDst->wBitsPerSample){
    case 8:
        break;
    case 16:
        idx += 4;
        break;
    case 24:
        if (adsi->pwfxDst->nBlockAlign != 3 * adsi->pwfxDst->nChannels) {
            FIXME("Destination: 24-bit samples must be packed\n");
            return MMSYSERR_NOTSUPPORTED;
        }
        idx += 8;
        break;
    default:
        FIXME("Unsupported destination bit depth: %u\n", adsi->pwfxDst->wBitsPerSample);
        return MMSYSERR_NOTSUPPORTED;
    }

    if (adsi->pwfxSrc->nChannels      == 1)  idx += 2;

    if (adsi->pwfxDst->nChannels      == 1)  idx += 1;

    apd = HeapAlloc(GetProcessHeap(), 0, sizeof(AcmPcmData));
    if (!apd)
        return MMSYSERR_NOMEM;

    if (adsi->pwfxSrc->nSamplesPerSec == adsi->pwfxDst->nSamplesPerSec) {
        flags = 0;
        apd->cvt.cvtKeepRate = PCM_ConvertKeepRate[idx];
    } else {
        flags = PCM_RESAMPLE;
        apd->cvt.cvtChangeRate = PCM_ConvertChangeRate[idx];
    }

    if(!apd->cvt.cvtChangeRate && !apd->cvt.cvtKeepRate){
        FIXME("Unimplemented conversion from %u -> %u bps\n",
            adsi->pwfxSrc->wBitsPerSample,
            adsi->pwfxDst->wBitsPerSample);
        HeapFree(GetProcessHeap(), 0, apd);
        return MMSYSERR_NOTSUPPORTED;
    }

    adsi->dwDriver = (DWORD_PTR)apd;
    adsi->fdwDriver = flags;

    return MMSYSERR_NOERROR;
}