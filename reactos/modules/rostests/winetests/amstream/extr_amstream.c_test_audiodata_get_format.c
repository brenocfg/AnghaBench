#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int wFormatTag; int nChannels; int nSamplesPerSec; int nAvgBytesPerSec; int nBlockAlign; int wBitsPerSample; int cbSize; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IAudioData ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_POINTER ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IAudioData_GetFormat (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IAudioData_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioData ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/ * create_audio_data () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_audiodata_get_format(void)
{
    IUnknown *unknown = create_audio_data();
    IAudioData *audio_data = NULL;
    WAVEFORMATEX wave_format = {0};

    HRESULT result;

    result = IUnknown_QueryInterface(unknown, &IID_IAudioData, (void **)&audio_data);
    if (FAILED(result))
    {
        /* test_audiodata_query_interface handles this case */
        skip("No IAudioData\n");
        goto out_unknown;
    }

    result = IAudioData_GetFormat(audio_data, NULL);
    ok(E_POINTER == result, "got 0x%08x\n", result);

    wave_format.wFormatTag = 0xdead;
    wave_format.nChannels = 0xdead;
    wave_format.nSamplesPerSec = 0xdeadbeef;
    wave_format.nAvgBytesPerSec = 0xdeadbeef;
    wave_format.nBlockAlign = 0xdead;
    wave_format.wBitsPerSample = 0xdead;
    wave_format.cbSize = 0xdead;
    result = IAudioData_GetFormat(audio_data, &wave_format);
    ok(S_OK == result, "got 0x%08x\n", result);
    ok(WAVE_FORMAT_PCM == wave_format.wFormatTag, "got %u\n", wave_format.wFormatTag);
    ok(1 == wave_format.nChannels, "got %u\n", wave_format.nChannels);
    ok(11025 == wave_format.nSamplesPerSec, "got %u\n", wave_format.nSamplesPerSec);
    ok(22050 == wave_format.nAvgBytesPerSec, "got %u\n", wave_format.nAvgBytesPerSec);
    ok(2 == wave_format.nBlockAlign, "got %u\n", wave_format.nBlockAlign);
    ok(16 == wave_format.wBitsPerSample, "got %u\n", wave_format.wBitsPerSample);
    ok(0 == wave_format.cbSize, "got %u\n", wave_format.cbSize);

    IAudioData_Release(audio_data);

out_unknown:
    IUnknown_Release(unknown);
}