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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IAudioData ;
typedef  int HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int E_INVALIDARG ; 
 scalar_t__ FAILED (int) ; 
 int IAudioData_GetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IAudioData_Release (int /*<<< orphan*/ *) ; 
 int IAudioData_SetActual (int /*<<< orphan*/ *,int) ; 
 int IAudioData_SetBuffer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IAudioData ; 
 int IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/ * create_audio_data () ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_audiodata_set_actual(void)
{
    IUnknown *unknown = create_audio_data();
    IAudioData *audio_data = NULL;
    BYTE buffer[100] = {0};
    DWORD actual_data = 0;

    HRESULT result;

    result = IUnknown_QueryInterface(unknown, &IID_IAudioData, (void **)&audio_data);
    if (FAILED(result))
    {
        /* test_audiodata_query_interface handles this case */
        skip("No IAudioData\n");
        goto out_unknown;
    }

    result = IAudioData_SetActual(audio_data, 0);
    ok(S_OK == result, "got 0x%08x\n", result);

    result = IAudioData_SetBuffer(audio_data, sizeof(buffer), buffer, 0);
    ok(S_OK == result, "got 0x%08x\n", result);

    result = IAudioData_SetActual(audio_data, sizeof(buffer) + 1);
    ok(E_INVALIDARG == result, "got 0x%08x\n", result);

    result = IAudioData_SetActual(audio_data, sizeof(buffer));
    ok(S_OK == result, "got 0x%08x\n", result);

    actual_data = 0xdeadbeef;
    result = IAudioData_GetInfo(audio_data, NULL, NULL, &actual_data);
    ok(S_OK == result, "got 0x%08x\n", result);
    ok(sizeof(buffer) == actual_data, "got %u\n", actual_data);

    result = IAudioData_SetActual(audio_data, 0);
    ok(S_OK == result, "got 0x%08x\n", result);

    actual_data = 0xdeadbeef;
    result = IAudioData_GetInfo(audio_data, NULL, NULL, &actual_data);
    ok(S_OK == result, "got 0x%08x\n", result);
    ok(0 == actual_data, "got %u\n", actual_data);

    IAudioData_Release(audio_data);

out_unknown:
    IUnknown_Release(unknown);
}