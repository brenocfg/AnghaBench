#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nSamplesPerSec; int wBitsPerSample; int nChannels; int nBlockAlign; int nAvgBytesPerSec; scalar_t__ cbSize; int /*<<< orphan*/  wFormatTag; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
typedef  int /*<<< orphan*/  IAudioClient ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  AUDCLNT_SHAREMODE ;

/* Variables and functions */
 int ARRAY_SIZE (void***) ; 
 int /*<<< orphan*/  AUDCLNT_E_ENDPOINT_CREATE_FAILED ; 
 int /*<<< orphan*/  AUDCLNT_E_EXCLUSIVE_MODE_NOT_ALLOWED ; 
 int /*<<< orphan*/  AUDCLNT_E_UNSUPPORTED_FORMAT ; 
 int /*<<< orphan*/  AUDCLNT_SHAREMODE_SHARED ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_1__*) ; 
 int /*<<< orphan*/  IAudioClient_GetMixFormat (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  IAudioClient_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioClient_IsFormatSupported (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__**) ; 
 int /*<<< orphan*/  IAudioClient_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioClient ; 
 int /*<<< orphan*/  IMMDevice_Activate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  hexcl ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  trace (char*,char*,scalar_t__,int,int,...) ; 
 void*** win_formats ; 

__attribute__((used)) static void test_formats(AUDCLNT_SHAREMODE mode)
{
    IAudioClient *ac;
    HRESULT hr, hrs;
    WAVEFORMATEX fmt, *pwfx, *pwfx2;
    int i;

    fmt.wFormatTag = WAVE_FORMAT_PCM;
    fmt.cbSize = 0;

    for(i = 0; i < ARRAY_SIZE(win_formats); i++) {
        hr = IMMDevice_Activate(dev, &IID_IAudioClient, CLSCTX_INPROC_SERVER,
                NULL, (void**)&ac);
        ok(hr == S_OK, "Activation failed with %08x\n", hr);
        if(hr != S_OK)
            continue;

        hr = IAudioClient_GetMixFormat(ac, &pwfx);
        ok(hr == S_OK, "GetMixFormat failed: %08x\n", hr);

        fmt.nSamplesPerSec = win_formats[i][0];
        fmt.wBitsPerSample = win_formats[i][1];
        fmt.nChannels      = win_formats[i][2];
        fmt.nBlockAlign    = fmt.nChannels * fmt.wBitsPerSample / 8;
        fmt.nAvgBytesPerSec= fmt.nBlockAlign * fmt.nSamplesPerSec;

        pwfx2 = (WAVEFORMATEX*)0xDEADF00D;
        hr = IAudioClient_IsFormatSupported(ac, mode, &fmt, &pwfx2);
        hrs = hr;
        /* Only shared mode suggests something ... GetMixFormat! */
        ok(hr == S_OK || (mode == AUDCLNT_SHAREMODE_SHARED
           ? hr == S_FALSE || broken(hr == AUDCLNT_E_UNSUPPORTED_FORMAT &&
               /* 5:1 card exception when asked for 1 channel at mixer rate */
               pwfx->nChannels > 2 && fmt.nSamplesPerSec == pwfx->nSamplesPerSec)
           : (hr == AUDCLNT_E_UNSUPPORTED_FORMAT || hr == hexcl)),
           "IsFormatSupported(%d, %ux%2ux%u) returns %08x\n", mode,
           fmt.nSamplesPerSec, fmt.wBitsPerSample, fmt.nChannels, hr);
        if (hr == S_OK)
            trace("IsSupported(%s, %ux%2ux%u)\n",
                  mode == AUDCLNT_SHAREMODE_SHARED ? "shared " : "exclus.",
                  fmt.nSamplesPerSec, fmt.wBitsPerSample, fmt.nChannels);

        /* Change GetMixFormat wBitsPerSample only => S_OK */
        if (mode == AUDCLNT_SHAREMODE_SHARED
            && fmt.nSamplesPerSec == pwfx->nSamplesPerSec
            && fmt.nChannels == pwfx->nChannels)
            ok(hr == S_OK, "Varying BitsPerSample %u\n", fmt.wBitsPerSample);

        ok((hr == S_FALSE)^(pwfx2 == NULL), "hr %x<->suggest %p\n", hr, pwfx2);
        if (pwfx2 == (WAVEFORMATEX*)0xDEADF00D)
            pwfx2 = NULL; /* broken in Wine < 1.3.28 */
        if (pwfx2) {
            ok(pwfx2->nSamplesPerSec == pwfx->nSamplesPerSec &&
               pwfx2->nChannels      == pwfx->nChannels &&
               pwfx2->wBitsPerSample == pwfx->wBitsPerSample,
               "Suggestion %ux%2ux%u differs from GetMixFormat\n",
               pwfx2->nSamplesPerSec, pwfx2->wBitsPerSample, pwfx2->nChannels);
        }

        /* Vista returns E_INVALIDARG upon AUDCLNT_STREAMFLAGS_RATEADJUST */
        hr = IAudioClient_Initialize(ac, mode, 0, 5000000, 0, &fmt, NULL);
        if ((hrs == S_OK) ^ (hr == S_OK))
            trace("Initialize (%s, %ux%2ux%u) returns %08x unlike IsFormatSupported\n",
                  mode == AUDCLNT_SHAREMODE_SHARED ? "shared " : "exclus.",
                  fmt.nSamplesPerSec, fmt.wBitsPerSample, fmt.nChannels, hr);
        if (mode == AUDCLNT_SHAREMODE_SHARED)
            ok(hrs == S_OK ? hr == S_OK : hr == AUDCLNT_E_UNSUPPORTED_FORMAT,
               "Initialize(shared,  %ux%2ux%u) returns %08x\n",
               fmt.nSamplesPerSec, fmt.wBitsPerSample, fmt.nChannels, hr);
        else if (hrs == AUDCLNT_E_EXCLUSIVE_MODE_NOT_ALLOWED)
            /* Unsupported format implies "create failed" and shadows "not allowed" */
            ok(hrs == hexcl && (hr == AUDCLNT_E_ENDPOINT_CREATE_FAILED || hr == hrs),
               "Initialize(noexcl., %ux%2ux%u) returns %08x(%08x)\n",
               fmt.nSamplesPerSec, fmt.wBitsPerSample, fmt.nChannels, hr, hrs);
        else
            /* On testbot 48000x16x1 claims support, but does not Initialize.
             * Some cards Initialize 44100|48000x16x1 yet claim no support;
             * F. Gouget's w7 bots do that for 12000|96000x8|16x1|2 */
            ok(hrs == S_OK ? hr == S_OK || broken(hr == AUDCLNT_E_ENDPOINT_CREATE_FAILED)
               : hr == AUDCLNT_E_ENDPOINT_CREATE_FAILED || hr == AUDCLNT_E_UNSUPPORTED_FORMAT ||
                 broken(hr == S_OK &&
                     ((fmt.nChannels == 1 && fmt.wBitsPerSample == 16) ||
                      (fmt.nSamplesPerSec == 12000 || fmt.nSamplesPerSec == 96000))),
               "Initialize(exclus., %ux%2ux%u) returns %08x\n",
               fmt.nSamplesPerSec, fmt.wBitsPerSample, fmt.nChannels, hr);

        /* Bug in native (Vista/w2k8/w7): after Initialize failed, better
         * Release this ac and Activate a new one.
         * A second call (with a known working format) would yield
         * ALREADY_INITIALIZED in shared mode yet be unusable, and in exclusive
         * mode some entity keeps a lock on the device, causing DEVICE_IN_USE to
         * all subsequent calls until the audio engine service is restarted. */

        CoTaskMemFree(pwfx2);
        CoTaskMemFree(pwfx);
        IAudioClient_Release(ac);
    }
}