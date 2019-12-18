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
typedef  scalar_t__ OAFilterState ;
typedef  int /*<<< orphan*/  IMediaControl ;
typedef  int /*<<< orphan*/  IFilterGraph2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IFilterGraph2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IMediaControl ; 
 scalar_t__ IMediaControl_GetState (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 scalar_t__ IMediaControl_Pause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMediaControl_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IMediaControl_Run (int /*<<< orphan*/ *) ; 
 scalar_t__ IMediaControl_Stop (int /*<<< orphan*/ *) ; 
 int INFINITE ; 
 int SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ State_Paused ; 
 scalar_t__ State_Running ; 
 scalar_t__ State_Stopped ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_state_change(IFilterGraph2 *graph)
{
    IMediaControl *control;
    OAFilterState state;
    HRESULT hr;

    hr = IFilterGraph2_QueryInterface(graph, &IID_IMediaControl, (void **)&control);
    ok(hr == S_OK, "QueryInterface(IMediaControl) failed: %x\n", hr);

    hr = IMediaControl_GetState(control, 1000, &state);
    ok(hr == S_OK, "GetState() failed: %x\n", hr);
    ok(state == State_Stopped, "wrong state %d\n", state);

    hr = IMediaControl_Run(control);
    ok(SUCCEEDED(hr), "Run() failed: %x\n", hr);
    hr = IMediaControl_GetState(control, INFINITE, &state);
    ok(SUCCEEDED(hr), "GetState() failed: %x\n", hr);
    ok(state == State_Running, "wrong state %d\n", state);

    hr = IMediaControl_Stop(control);
    ok(SUCCEEDED(hr), "Stop() failed: %x\n", hr);
    hr = IMediaControl_GetState(control, 1000, &state);
    ok(hr == S_OK, "GetState() failed: %x\n", hr);
    ok(state == State_Stopped, "wrong state %d\n", state);

    hr = IMediaControl_Pause(control);
    ok(SUCCEEDED(hr), "Pause() failed: %x\n", hr);
    hr = IMediaControl_GetState(control, 1000, &state);
    ok(hr == S_OK, "GetState() failed: %x\n", hr);
    ok(state == State_Paused, "wrong state %d\n", state);

    hr = IMediaControl_Run(control);
    ok(SUCCEEDED(hr), "Run() failed: %x\n", hr);
    hr = IMediaControl_GetState(control, 1000, &state);
    ok(hr == S_OK, "GetState() failed: %x\n", hr);
    ok(state == State_Running, "wrong state %d\n", state);

    hr = IMediaControl_Pause(control);
    ok(SUCCEEDED(hr), "Pause() failed: %x\n", hr);
    hr = IMediaControl_GetState(control, 1000, &state);
    ok(hr == S_OK, "GetState() failed: %x\n", hr);
    ok(state == State_Paused, "wrong state %d\n", state);

    hr = IMediaControl_Stop(control);
    ok(SUCCEEDED(hr), "Stop() failed: %x\n", hr);
    hr = IMediaControl_GetState(control, 1000, &state);
    ok(hr == S_OK, "GetState() failed: %x\n", hr);
    ok(state == State_Stopped, "wrong state %d\n", state);

    IMediaControl_Release(control);
}