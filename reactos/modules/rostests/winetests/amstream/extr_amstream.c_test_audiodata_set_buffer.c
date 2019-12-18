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
typedef  int /*<<< orphan*/ * HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/ * E_INVALIDARG ; 
 scalar_t__ FAILED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IAudioData_GetInfo (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioData_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IAudioData_SetBuffer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IAudioData ; 
 int /*<<< orphan*/ * IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/ * create_audio_data () ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_audiodata_set_buffer(void)
{
    IUnknown *unknown = create_audio_data();
    IAudioData *audio_data = NULL;
    BYTE buffer[100] = {0};
    DWORD length = 0;
    BYTE *data = NULL;

    HRESULT result;

    result = IUnknown_QueryInterface(unknown, &IID_IAudioData, (void **)&audio_data);
    if (FAILED(result))
    {
        /* test_audiodata_query_interface handles this case */
        skip("No IAudioData\n");
        goto out_unknown;
    }

    result = IAudioData_SetBuffer(audio_data, 100, NULL, 0);
    ok(S_OK == result, "got 0x%08x\n", result);

    data = (BYTE *)0xdeadbeef;
    length = 0xdeadbeef;
    result = IAudioData_GetInfo(audio_data, &length, &data, NULL);
    ok(S_OK == result, "got 0x%08x\n", result);
    ok(100 == length, "got %u\n", length);
    ok(NULL != data, "got %p\n", data);

    result = IAudioData_SetBuffer(audio_data, 0, buffer, 0);
    ok(E_INVALIDARG == result, "got 0x%08x\n", result);

    result = IAudioData_SetBuffer(audio_data, sizeof(buffer), buffer, 0);
    ok(S_OK == result, "got 0x%08x\n", result);

    data = (BYTE *)0xdeadbeef;
    length = 0xdeadbeef;
    result = IAudioData_GetInfo(audio_data, &length, &data, NULL);
    ok(S_OK == result, "got 0x%08x\n", result);
    ok(sizeof(buffer) == length, "got %u\n", length);
    ok(buffer == data, "got %p\n", data);

    IAudioData_Release(audio_data);

out_unknown:
    IUnknown_Release(unknown);
}