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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IMemoryData ;
typedef  int /*<<< orphan*/  IAudioData ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ IAudioData_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IAudioData_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioData ; 
 int /*<<< orphan*/  IID_IMemoryData ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_audio_data () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_audiodata_query_interface(void)
{
    IUnknown *unknown = create_audio_data();
    IMemoryData *memory_data = NULL;
    IAudioData *audio_data = NULL;

    HRESULT result;

    result = IUnknown_QueryInterface(unknown, &IID_IMemoryData, (void **)&memory_data);
    ok(E_NOINTERFACE == result, "got 0x%08x\n", result);

    result = IUnknown_QueryInterface(unknown, &IID_IAudioData, (void **)&audio_data);
    ok(S_OK == result, "got 0x%08x\n", result);
    if (S_OK == result)
    {
        result = IAudioData_QueryInterface(audio_data, &IID_IMemoryData, (void **)&memory_data);
        ok(E_NOINTERFACE == result, "got 0x%08x\n", result);

        IAudioData_Release(audio_data);
    }

    IUnknown_Release(unknown);
}