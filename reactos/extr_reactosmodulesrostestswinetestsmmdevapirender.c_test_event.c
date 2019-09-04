#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
typedef  int /*<<< orphan*/  IAudioClient ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ AUDCLNT_E_EVENTHANDLE_NOT_SET ; 
 int /*<<< orphan*/  AUDCLNT_SHAREMODE_SHARED ; 
 int /*<<< orphan*/  AUDCLNT_STREAMFLAGS_EVENTCALLBACK ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ D3D11_ERROR_4E ; 
 int /*<<< orphan*/  ERROR_INVALID_NAME ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_UNEXPECTED ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 scalar_t__ IAudioClient_GetMixFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IAudioClient_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioClient_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioClient_Reset (int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioClient_SetEventHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioClient_Start (int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioClient_Stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioClient ; 
 scalar_t__ IMMDevice_Activate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ResetEvent (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_event(void)
{
    HANDLE event;
    HRESULT hr;
    DWORD r;
    IAudioClient *ac;
    WAVEFORMATEX *pwfx;

    hr = IMMDevice_Activate(dev, &IID_IAudioClient, CLSCTX_INPROC_SERVER,
            NULL, (void**)&ac);
    ok(hr == S_OK, "Activation failed with %08x\n", hr);
    if(hr != S_OK)
        return;

    hr = IAudioClient_GetMixFormat(ac, &pwfx);
    ok(hr == S_OK, "GetMixFormat failed: %08x\n", hr);

    hr = IAudioClient_Initialize(ac, AUDCLNT_SHAREMODE_SHARED,
            AUDCLNT_STREAMFLAGS_EVENTCALLBACK, 5000000,
            0, pwfx, NULL);
    ok(hr == S_OK, "Initialize failed: %08x\n", hr);

    CoTaskMemFree(pwfx);

    event = CreateEventW(NULL, FALSE, FALSE, NULL);
    ok(event != NULL, "CreateEvent failed\n");

    hr = IAudioClient_Start(ac);
    ok(hr == AUDCLNT_E_EVENTHANDLE_NOT_SET ||
            hr == D3D11_ERROR_4E /* win10 */, "Start failed: %08x\n", hr);

    hr = IAudioClient_SetEventHandle(ac, event);
    ok(hr == S_OK, "SetEventHandle failed: %08x\n", hr);

    hr = IAudioClient_SetEventHandle(ac, event);
    ok(hr == HRESULT_FROM_WIN32(ERROR_INVALID_NAME) ||
            hr == E_UNEXPECTED /* win10 */, "SetEventHandle returns %08x\n", hr);

    r = WaitForSingleObject(event, 40);
    ok(r == WAIT_TIMEOUT, "Wait(event) before Start gave %x\n", r);

    hr = IAudioClient_Start(ac);
    ok(hr == S_OK, "Start failed: %08x\n", hr);

    r = WaitForSingleObject(event, 20);
    ok(r == WAIT_OBJECT_0, "Wait(event) after Start gave %x\n", r);

    hr = IAudioClient_Stop(ac);
    ok(hr == S_OK, "Stop failed: %08x\n", hr);

    ok(ResetEvent(event), "ResetEvent\n");

    /* Still receiving events! */
    r = WaitForSingleObject(event, 20);
    ok(r == WAIT_OBJECT_0, "Wait(event) after Stop gave %x\n", r);

    hr = IAudioClient_Reset(ac);
    ok(hr == S_OK, "Reset failed: %08x\n", hr);

    ok(ResetEvent(event), "ResetEvent\n");

    r = WaitForSingleObject(event, 120);
    ok(r == WAIT_OBJECT_0, "Wait(event) after Reset gave %x\n", r);

    hr = IAudioClient_SetEventHandle(ac, NULL);
    ok(hr == E_INVALIDARG, "SetEventHandle(NULL) returns %08x\n", hr);

    r = WaitForSingleObject(event, 70);
    ok(r == WAIT_OBJECT_0, "Wait(NULL event) gave %x\n", r);

    /* test releasing a playing stream */
    hr = IAudioClient_Start(ac);
    ok(hr == S_OK, "Start failed: %08x\n", hr);
    IAudioClient_Release(ac);

    CloseHandle(event);
}