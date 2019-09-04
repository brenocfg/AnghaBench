#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONG ;
struct TYPE_10__ {int FormatSize; } ;
struct TYPE_7__ {int /*<<< orphan*/  Specifier; int /*<<< orphan*/  SubFormat; int /*<<< orphan*/  MajorFormat; } ;
struct TYPE_9__ {int /*<<< orphan*/  MaximumChannels; int /*<<< orphan*/  MaximumBitsPerSample; int /*<<< orphan*/  MinimumBitsPerSample; int /*<<< orphan*/  MaximumSampleFrequency; int /*<<< orphan*/  MinimumSampleFrequency; TYPE_1__ DataRange; } ;
struct TYPE_8__ {scalar_t__ Count; } ;
typedef  TYPE_2__* PKSMULTIPLE_ITEM ;
typedef  TYPE_3__* PKSDATARANGE_AUDIO ;
typedef  TYPE_4__* PKSDATARANGE ;
typedef  int /*<<< orphan*/  MIXER_STATUS ;
typedef  int /*<<< orphan*/  KSDATARANGE_AUDIO ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsEqualGUIDAligned (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KSDATAFORMAT_SPECIFIER_WAVEFORMATEX ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_PCM ; 
 int /*<<< orphan*/  KSDATAFORMAT_TYPE_AUDIO ; 
 int /*<<< orphan*/  MM_STATUS_SUCCESS ; 
 int /*<<< orphan*/  MM_STATUS_UNSUCCESSFUL ; 

MIXER_STATUS
MMixerFindAudioDataRange(
    PKSMULTIPLE_ITEM MultipleItem,
    PKSDATARANGE_AUDIO * OutDataRangeAudio)
{
    ULONG Index;
    PKSDATARANGE_AUDIO DataRangeAudio;
    PKSDATARANGE DataRange;

    DataRange = (PKSDATARANGE) (MultipleItem + 1);
    for(Index = 0; Index < MultipleItem->Count; Index++)
    {
        if (DataRange->FormatSize == sizeof(KSDATARANGE_AUDIO))
        {
            DataRangeAudio = (PKSDATARANGE_AUDIO)DataRange;
            if (IsEqualGUIDAligned(&DataRangeAudio->DataRange.MajorFormat, &KSDATAFORMAT_TYPE_AUDIO) &&
                IsEqualGUIDAligned(&DataRangeAudio->DataRange.SubFormat, &KSDATAFORMAT_SUBTYPE_PCM) &&
                IsEqualGUIDAligned(&DataRangeAudio->DataRange.Specifier, &KSDATAFORMAT_SPECIFIER_WAVEFORMATEX))
            {
                DPRINT("Min Sample %u Max Sample %u Min Bits %u Max Bits %u Max Channel %u\n", DataRangeAudio->MinimumSampleFrequency, DataRangeAudio->MaximumSampleFrequency,
                                                         DataRangeAudio->MinimumBitsPerSample, DataRangeAudio->MaximumBitsPerSample, DataRangeAudio->MaximumChannels);
                *OutDataRangeAudio = DataRangeAudio;
                return MM_STATUS_SUCCESS;
            }
        }
        DataRange = (PKSDATARANGE)((ULONG_PTR)DataRange + DataRange->FormatSize);
    }
    return MM_STATUS_UNSUCCESSFUL;
}