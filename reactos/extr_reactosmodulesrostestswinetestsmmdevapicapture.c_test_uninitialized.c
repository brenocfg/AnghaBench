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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  REFERENCE_TIME ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IAudioClient ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__ AUDCLNT_E_NOT_INITIALIZED ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IAudioClient_GetBufferSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioClient_GetCurrentPadding (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioClient_GetService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IAudioClient_GetStreamLatency (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioClient_Reset (int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioClient_SetEventHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IAudioClient_Start (int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioClient_Stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioStreamVolume ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_uninitialized(IAudioClient *ac)
{
    HRESULT hr;
    UINT32 num;
    REFERENCE_TIME t1;

    HANDLE handle = CreateEventW(NULL, FALSE, FALSE, NULL);
    IUnknown *unk;

    hr = IAudioClient_GetBufferSize(ac, &num);
    ok(hr == AUDCLNT_E_NOT_INITIALIZED, "Uninitialized GetBufferSize call returns %08x\n", hr);

    hr = IAudioClient_GetStreamLatency(ac, &t1);
    ok(hr == AUDCLNT_E_NOT_INITIALIZED, "Uninitialized GetStreamLatency call returns %08x\n", hr);

    hr = IAudioClient_GetCurrentPadding(ac, &num);
    ok(hr == AUDCLNT_E_NOT_INITIALIZED, "Uninitialized GetCurrentPadding call returns %08x\n", hr);

    hr = IAudioClient_Start(ac);
    ok(hr == AUDCLNT_E_NOT_INITIALIZED, "Uninitialized Start call returns %08x\n", hr);

    hr = IAudioClient_Stop(ac);
    ok(hr == AUDCLNT_E_NOT_INITIALIZED, "Uninitialized Stop call returns %08x\n", hr);

    hr = IAudioClient_Reset(ac);
    ok(hr == AUDCLNT_E_NOT_INITIALIZED, "Uninitialized Reset call returns %08x\n", hr);

    hr = IAudioClient_SetEventHandle(ac, handle);
    ok(hr == AUDCLNT_E_NOT_INITIALIZED, "Uninitialized SetEventHandle call returns %08x\n", hr);

    hr = IAudioClient_GetService(ac, &IID_IAudioStreamVolume, (void**)&unk);
    ok(hr == AUDCLNT_E_NOT_INITIALIZED, "Uninitialized GetService call returns %08x\n", hr);

    CloseHandle(handle);
}