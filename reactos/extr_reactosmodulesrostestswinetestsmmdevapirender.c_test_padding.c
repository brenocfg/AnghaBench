#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int wBitsPerSample; int nSamplesPerSec; size_t nBlockAlign; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  size_t UINT32 ;
typedef  int REFERENCE_TIME ;
typedef  int /*<<< orphan*/  IAudioRenderClient ;
typedef  int /*<<< orphan*/  IAudioClient ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  AUDCLNT_BUFFERFLAGS_SILENT ; 
 int /*<<< orphan*/  AUDCLNT_E_BUFFER_OPERATION_PENDING ; 
 int /*<<< orphan*/  AUDCLNT_E_BUFFER_TOO_LARGE ; 
 int /*<<< orphan*/  AUDCLNT_E_INVALID_SIZE ; 
 int /*<<< orphan*/  AUDCLNT_E_OUT_OF_ORDER ; 
 int /*<<< orphan*/  AUDCLNT_SHAREMODE_SHARED ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_1__*) ; 
 int /*<<< orphan*/  IAudioClient_GetCurrentPadding (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  IAudioClient_GetDevicePeriod (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IAudioClient_GetMixFormat (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  IAudioClient_GetService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IAudioClient_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioClient_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioClient_Reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioRenderClient_GetBuffer (int /*<<< orphan*/ *,size_t,int**) ; 
 int /*<<< orphan*/  IAudioRenderClient_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioRenderClient_ReleaseBuffer (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IAudioClient ; 
 int /*<<< orphan*/  IID_IAudioRenderClient ; 
 int /*<<< orphan*/  IMMDevice_Activate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int MulDiv (int,int,int) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win10 ; 

__attribute__((used)) static void test_padding(void)
{
    HRESULT hr;
    IAudioClient *ac;
    IAudioRenderClient *arc;
    WAVEFORMATEX *pwfx;
    REFERENCE_TIME minp, defp;
    BYTE *buf, silence;
    UINT32 psize, pad, written, i;

    hr = IMMDevice_Activate(dev, &IID_IAudioClient, CLSCTX_INPROC_SERVER,
            NULL, (void**)&ac);
    ok(hr == S_OK, "Activation failed with %08x\n", hr);
    if(hr != S_OK)
        return;

    hr = IAudioClient_GetMixFormat(ac, &pwfx);
    ok(hr == S_OK, "GetMixFormat failed: %08x\n", hr);
    if(hr != S_OK)
        return;

    hr = IAudioClient_Initialize(ac, AUDCLNT_SHAREMODE_SHARED,
            0, 5000000, 0, pwfx, NULL);
    ok(hr == S_OK, "Initialize failed: %08x\n", hr);
    if(hr != S_OK)
        return;

    if(pwfx->wBitsPerSample == 8)
        silence = 128;
    else
        silence = 0;

    /** GetDevicePeriod
     * Default (= shared) device period is 10ms (e.g. 441 frames at 44100),
     * except when the HW/OS forces a particular alignment,
     * e.g. 10.1587ms is 28 * 16 = 448 frames at 44100 with HDA.
     * 441 observed with Vista, 448 with w7 on the same HW! */
    hr = IAudioClient_GetDevicePeriod(ac, &defp, &minp);
    ok(hr == S_OK, "GetDevicePeriod failed: %08x\n", hr);
    /* some wineXYZ.drv use 20ms, not seen on native */
    ok(defp == 100000 || broken(defp == 101587) || defp == 200000,
       "Expected 10ms default period: %u\n", (ULONG)defp);
    ok(minp != 0, "Minimum period is 0\n");
    ok(minp <= defp, "Minimum period is greater than default period\n");

    hr = IAudioClient_GetService(ac, &IID_IAudioRenderClient, (void**)&arc);
    ok(hr == S_OK, "GetService failed: %08x\n", hr);

    psize = MulDiv(defp, pwfx->nSamplesPerSec, 10000000) * 10;

    written = 0;
    hr = IAudioClient_GetCurrentPadding(ac, &pad);
    ok(hr == S_OK, "GetCurrentPadding failed: %08x\n", hr);
    ok(pad == written, "GetCurrentPadding returned %u, should be %u\n", pad, written);

    hr = IAudioRenderClient_GetBuffer(arc, psize, &buf);
    ok(hr == S_OK, "GetBuffer failed: %08x\n", hr);
    ok(buf != NULL, "NULL buffer returned\n");
    if(!win10){
        /* win10 appears not to clear the buffer */
        for(i = 0; i < psize * pwfx->nBlockAlign; ++i){
            if(buf[i] != silence){
                ok(0, "buffer has data in it already, i: %u, valu: %f\n", i, *((float*)buf));
                break;
            }
        }
    }

    hr = IAudioRenderClient_GetBuffer(arc, 0, &buf);
    ok(hr == AUDCLNT_E_OUT_OF_ORDER, "GetBuffer 0 size failed: %08x\n", hr);
    ok(buf == NULL, "GetBuffer 0 gave %p\n", buf);
    /* MSDN instead documents buf remains untouched */

    hr = IAudioClient_Reset(ac);
    ok(hr == AUDCLNT_E_BUFFER_OPERATION_PENDING, "Reset failed: %08x\n", hr);

    hr = IAudioRenderClient_ReleaseBuffer(arc, psize,
            AUDCLNT_BUFFERFLAGS_SILENT);
    ok(hr == S_OK, "ReleaseBuffer failed: %08x\n", hr);
    if(hr == S_OK) written += psize;

    hr = IAudioClient_GetCurrentPadding(ac, &pad);
    ok(hr == S_OK, "GetCurrentPadding failed: %08x\n", hr);
    ok(pad == written, "GetCurrentPadding returned %u, should be %u\n", pad, written);

    psize = MulDiv(minp, pwfx->nSamplesPerSec, 10000000) * 10;

    hr = IAudioRenderClient_GetBuffer(arc, psize, &buf);
    ok(hr == S_OK, "GetBuffer failed: %08x\n", hr);
    ok(buf != NULL, "NULL buffer returned\n");

    hr = IAudioRenderClient_ReleaseBuffer(arc, psize,
            AUDCLNT_BUFFERFLAGS_SILENT);
    ok(hr == S_OK, "ReleaseBuffer failed: %08x\n", hr);
    written += psize;

    hr = IAudioClient_GetCurrentPadding(ac, &pad);
    ok(hr == S_OK, "GetCurrentPadding failed: %08x\n", hr);
    ok(pad == written, "GetCurrentPadding returned %u, should be %u\n", pad, written);

    /* overfull buffer. requested 1/2s buffer size, so try
     * to get a 1/2s buffer, which should fail */
    psize = pwfx->nSamplesPerSec / 2;
    buf = (void*)0xDEADF00D;
    hr = IAudioRenderClient_GetBuffer(arc, psize, &buf);
    ok(hr == AUDCLNT_E_BUFFER_TOO_LARGE, "GetBuffer gave wrong error: %08x\n", hr);
    ok(buf == NULL, "NULL expected %p\n", buf);

    hr = IAudioRenderClient_ReleaseBuffer(arc, psize, 0);
    ok(hr == AUDCLNT_E_OUT_OF_ORDER, "ReleaseBuffer gave wrong error: %08x\n", hr);

    psize = MulDiv(minp, pwfx->nSamplesPerSec, 10000000) * 2;

    hr = IAudioRenderClient_GetBuffer(arc, psize, &buf);
    ok(hr == S_OK, "GetBuffer failed: %08x\n", hr);
    ok(buf != NULL, "NULL buffer returned\n");

    hr = IAudioRenderClient_ReleaseBuffer(arc, 0, 0);
    ok(hr == S_OK, "ReleaseBuffer 0 gave wrong error: %08x\n", hr);

    buf = (void*)0xDEADF00D;
    hr = IAudioRenderClient_GetBuffer(arc, 0, &buf);
    ok(hr == S_OK, "GetBuffer 0 size failed: %08x\n", hr);
    ok(buf == NULL, "GetBuffer 0 gave %p\n", buf);
    /* MSDN instead documents buf remains untouched */

    buf = (void*)0xDEADF00D;
    hr = IAudioRenderClient_GetBuffer(arc, 0, &buf);
    ok(hr == S_OK, "GetBuffer 0 size #2 failed: %08x\n", hr);
    ok(buf == NULL, "GetBuffer 0 #2 gave %p\n", buf);

    hr = IAudioRenderClient_ReleaseBuffer(arc, psize, 0);
    ok(hr == AUDCLNT_E_OUT_OF_ORDER, "ReleaseBuffer not size 0 gave %08x\n", hr);

    hr = IAudioRenderClient_GetBuffer(arc, psize, &buf);
    ok(hr == S_OK, "GetBuffer failed: %08x\n", hr);
    ok(buf != NULL, "NULL buffer returned\n");

    hr = IAudioRenderClient_ReleaseBuffer(arc, 0, 0);
    ok(hr == S_OK, "ReleaseBuffer 0 gave wrong error: %08x\n", hr);

    hr = IAudioClient_GetCurrentPadding(ac, &pad);
    ok(hr == S_OK, "GetCurrentPadding failed: %08x\n", hr);
    ok(pad == written, "GetCurrentPadding returned %u, should be %u\n", pad, written);

    hr = IAudioRenderClient_GetBuffer(arc, psize, &buf);
    ok(hr == S_OK, "GetBuffer failed: %08x\n", hr);
    ok(buf != NULL, "NULL buffer returned\n");

    hr = IAudioRenderClient_ReleaseBuffer(arc, psize+1, AUDCLNT_BUFFERFLAGS_SILENT);
    ok(hr == AUDCLNT_E_INVALID_SIZE, "ReleaseBuffer too large error: %08x\n", hr);
    /* todo_wine means Wine may overwrite memory */
    if(hr == S_OK) written += psize+1;

    /* Buffer still hold */
    hr = IAudioRenderClient_ReleaseBuffer(arc, psize/2, AUDCLNT_BUFFERFLAGS_SILENT);
    ok(hr == S_OK, "ReleaseBuffer after error: %08x\n", hr);
    if(hr == S_OK) written += psize/2;

    hr = IAudioRenderClient_ReleaseBuffer(arc, 0, 0);
    ok(hr == S_OK, "ReleaseBuffer 0 gave wrong error: %08x\n", hr);

    hr = IAudioClient_GetCurrentPadding(ac, &pad);
    ok(hr == S_OK, "GetCurrentPadding failed: %08x\n", hr);
    ok(pad == written, "GetCurrentPadding returned %u, should be %u\n", pad, written);

    CoTaskMemFree(pwfx);

    IAudioRenderClient_Release(arc);
    IAudioClient_Release(ac);
}