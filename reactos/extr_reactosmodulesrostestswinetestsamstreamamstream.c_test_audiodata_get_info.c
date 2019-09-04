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
typedef  int /*<<< orphan*/  IAudioData ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IAudioData_GetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioData_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioData ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ MS_E_NOTINIT ; 
 int /*<<< orphan*/ * create_audio_data () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_audiodata_get_info(void)
{
    IUnknown *unknown = create_audio_data();
    IAudioData *audio_data = NULL;

    HRESULT result;

    result = IUnknown_QueryInterface(unknown, &IID_IAudioData, (void **)&audio_data);
    if (FAILED(result))
    {
        /* test_audiodata_query_interface handles this case */
        skip("No IAudioData\n");
        goto out_unknown;
    }

    result = IAudioData_GetInfo(audio_data, NULL, NULL, NULL);
    ok(MS_E_NOTINIT == result, "got 0x%08x\n", result);

    IAudioData_Release(audio_data);

out_unknown:
    IUnknown_Release(unknown);
}