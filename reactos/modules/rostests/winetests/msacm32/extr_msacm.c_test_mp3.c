#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nSamplesPerSec; int wBitsPerSample; int nChannels; int nBlockAlign; int nAvgBytesPerSec; int /*<<< orphan*/  wFormatTag; scalar_t__ cbSize; } ;
typedef  TYPE_2__ WAVEFORMATEX ;
struct TYPE_6__ {int nSamplesPerSec; int nChannels; int nBlockAlign; int nAvgBytesPerSec; scalar_t__ cbSize; scalar_t__ wBitsPerSample; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_8__ {int nBlockSize; int nFramesPerBlock; TYPE_1__ wfx; void* wID; scalar_t__ nCodecDelay; scalar_t__ fdwFlags; } ;
typedef  TYPE_3__ MPEGLAYER3WAVEFORMAT ;
typedef  scalar_t__ MMRESULT ;
typedef  int /*<<< orphan*/  HACMSTREAM ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ ACMERR_NOTPOSSIBLE ; 
 int /*<<< orphan*/  ACM_STREAMSIZEF_SOURCE ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 void* MPEGLAYER3_ID_MPEG ; 
 scalar_t__ MPEGLAYER3_WFX_EXTRA_BYTES ; 
 int /*<<< orphan*/  WAVE_FORMAT_MPEGLAYER3 ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 scalar_t__ acmStreamClose (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ acmStreamOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ acmStreamSize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_mp3(void)
{
    MPEGLAYER3WAVEFORMAT src;
    WAVEFORMATEX dst;
    HACMSTREAM has;
    DWORD output;
    MMRESULT mr;

    src.wfx.wFormatTag = WAVE_FORMAT_MPEGLAYER3;
    src.wfx.nSamplesPerSec = 11025;
    src.wfx.wBitsPerSample = 0;
    src.wfx.nChannels = 1;
    src.wfx.nBlockAlign = 576;
    src.wfx.nAvgBytesPerSec = 2000;

    src.wID = MPEGLAYER3_ID_MPEG;
    src.fdwFlags = 0;
    src.nBlockSize = 576;
    src.nFramesPerBlock = 1;
    src.nCodecDelay = 0;

    dst.cbSize = 0;
    dst.wFormatTag = WAVE_FORMAT_PCM;
    dst.nSamplesPerSec = 11025;
    dst.wBitsPerSample = 16;
    dst.nChannels = 1;
    dst.nBlockAlign = dst.wBitsPerSample * dst.nChannels / 8;
    dst.nAvgBytesPerSec = dst.nSamplesPerSec * dst.nBlockAlign;

    src.wfx.cbSize = 0;

    mr = acmStreamOpen(&has, NULL, (WAVEFORMATEX*)&src, &dst, NULL, 0, 0, 0);
    ok(mr == ACMERR_NOTPOSSIBLE, "expected error ACMERR_NOTPOSSIBLE, got 0x%x\n", mr);
    if (mr == MMSYSERR_NOERROR) acmStreamClose(has, 0);

    src.wfx.cbSize = MPEGLAYER3_WFX_EXTRA_BYTES;
    src.wID = 0;

    mr = acmStreamOpen(&has, NULL, (WAVEFORMATEX*)&src, &dst, NULL, 0, 0, 0);
    ok(mr == ACMERR_NOTPOSSIBLE, "expected error ACMERR_NOTPOSSIBLE, got 0x%x\n", mr);
    if (mr == MMSYSERR_NOERROR) acmStreamClose(has, 0);

    src.wID = MPEGLAYER3_ID_MPEG;
    src.nBlockSize = 0;

    mr = acmStreamOpen(&has, NULL, (WAVEFORMATEX*)&src, &dst, NULL, 0, 0, 0);
    ok(mr == MMSYSERR_NOERROR || broken(mr == ACMERR_NOTPOSSIBLE) /* Win 2008 */,
       "failed with error 0x%x\n", mr);
    if (mr == MMSYSERR_NOERROR)
    {
       mr = acmStreamClose(has, 0);
       ok(mr == MMSYSERR_NOERROR, "failed with error 0x%x\n", mr);
    }
    src.nBlockSize = 576;
    src.wfx.nAvgBytesPerSec = 0;

    mr = acmStreamOpen(&has, NULL, (WAVEFORMATEX*)&src, &dst, NULL, 0, 0, 0);
    ok(mr == MMSYSERR_NOERROR || broken(mr == ACMERR_NOTPOSSIBLE) /* Win 2008 */,
       "failed with error 0x%x\n", mr);
    if (mr == MMSYSERR_NOERROR)
    {
       /* causes a division by zero exception in XP, Vista,
          but throws ACMERR_NOTPOSSIBLE on others */
       if (0) acmStreamSize(has, 4000, &output, ACM_STREAMSIZEF_SOURCE);
       mr = acmStreamClose(has, 0);
       ok(mr == MMSYSERR_NOERROR, "failed with error 0x%x\n", mr);
    }

    src.wfx.nAvgBytesPerSec = 2000;

    mr = acmStreamOpen(&has, NULL, (WAVEFORMATEX*)&src, &dst, NULL, 0, 0, 0);
    ok(mr == MMSYSERR_NOERROR || broken(mr == ACMERR_NOTPOSSIBLE) /* Win 2008 */,
       "failed with error 0x%x\n", mr);
    if (mr == MMSYSERR_NOERROR)
    {
       mr = acmStreamSize(has, 4000, &output, ACM_STREAMSIZEF_SOURCE);
       ok(mr == MMSYSERR_NOERROR, "failed with error 0x%x\n", mr);
       mr = acmStreamClose(has, 0);
       ok(mr == MMSYSERR_NOERROR, "failed with error 0x%x\n", mr);
    }
}