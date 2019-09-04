#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int wFormatTag; int nChannels; int nSamplesPerSec; int nAvgBytesPerSec; int nBlockAlign; int wBitsPerSample; int cbSize; } ;
struct TYPE_7__ {int wValidBitsPerSample; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {TYPE_4__ Format; int /*<<< orphan*/  SubFormat; int /*<<< orphan*/  dwChannelMask; TYPE_2__ Samples; TYPE_1__ member_0; } ;
typedef  TYPE_3__ WAVEFORMATPCMEX ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IAudioData ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_POINTER ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IAudioData_GetFormat (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  IAudioData_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioData_SetFormat (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  IID_IAudioData ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KSAUDIO_SPEAKER_STEREO ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_PCM ; 
 scalar_t__ S_OK ; 
 int WAVE_FORMAT_EXTENSIBLE ; 
 int WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/ * create_audio_data () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_audiodata_set_format(void)
{
    IUnknown *unknown = create_audio_data();
    IAudioData *audio_data = NULL;
    WAVEFORMATPCMEX wave_format = {{0}};

    HRESULT result;

    result = IUnknown_QueryInterface(unknown, &IID_IAudioData, (void **)&audio_data);
    if (FAILED(result))
    {
        /* test_audiodata_query_interface handles this case */
        skip("No IAudioData\n");
        goto out_unknown;
    }

    result = IAudioData_SetFormat(audio_data, NULL);
    ok(E_POINTER == result, "got 0x%08x\n", result);

    wave_format.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
    wave_format.Format.nChannels = 2;
    wave_format.Format.nSamplesPerSec = 44100;
    wave_format.Format.nAvgBytesPerSec = 176400;
    wave_format.Format.nBlockAlign = 4;
    wave_format.Format.wBitsPerSample = 16;
    wave_format.Format.cbSize = 22;
    wave_format.Samples.wValidBitsPerSample = 16;
    wave_format.dwChannelMask = KSAUDIO_SPEAKER_STEREO;
    wave_format.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
    result = IAudioData_SetFormat(audio_data, &wave_format.Format);
    ok(E_INVALIDARG == result, "got 0x%08x\n", result);

    wave_format.Format.wFormatTag = WAVE_FORMAT_PCM;
    wave_format.Format.nChannels = 2;
    wave_format.Format.nSamplesPerSec = 44100;
    wave_format.Format.nAvgBytesPerSec = 176400;
    wave_format.Format.nBlockAlign = 4;
    wave_format.Format.wBitsPerSample = 16;
    wave_format.Format.cbSize = 0;
    result = IAudioData_SetFormat(audio_data, &wave_format.Format);
    ok(S_OK == result, "got 0x%08x\n", result);

    wave_format.Format.wFormatTag = 0xdead;
    wave_format.Format.nChannels = 0xdead;
    wave_format.Format.nSamplesPerSec = 0xdeadbeef;
    wave_format.Format.nAvgBytesPerSec = 0xdeadbeef;
    wave_format.Format.nBlockAlign = 0xdead;
    wave_format.Format.wBitsPerSample = 0xdead;
    wave_format.Format.cbSize = 0xdead;
    result = IAudioData_GetFormat(audio_data, &wave_format.Format);
    ok(S_OK == result, "got 0x%08x\n", result);
    ok(WAVE_FORMAT_PCM == wave_format.Format.wFormatTag, "got %u\n", wave_format.Format.wFormatTag);
    ok(2 == wave_format.Format.nChannels, "got %u\n", wave_format.Format.nChannels);
    ok(44100 == wave_format.Format.nSamplesPerSec, "got %u\n", wave_format.Format.nSamplesPerSec);
    ok(176400 == wave_format.Format.nAvgBytesPerSec, "got %u\n", wave_format.Format.nAvgBytesPerSec);
    ok(4 == wave_format.Format.nBlockAlign, "got %u\n", wave_format.Format.nBlockAlign);
    ok(16 == wave_format.Format.wBitsPerSample, "got %u\n", wave_format.Format.wBitsPerSample);
    ok(0 == wave_format.Format.cbSize, "got %u\n", wave_format.Format.cbSize);

    IAudioData_Release(audio_data);

out_unknown:
    IUnknown_Release(unknown);
}