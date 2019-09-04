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
typedef  int /*<<< orphan*/  USHORT ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int* PVOID ;
typedef  int* PUSHORT ;
typedef  int* PULONG ;
typedef  int* PUCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int* ExAllocatePool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RtlMoveMemory (int*,int*,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
PerformChannelConversion(
    PUCHAR Buffer,
    ULONG BufferLength,
    ULONG OldChannels,
    ULONG NewChannels,
    ULONG BitsPerSample,
    PVOID * Result,
    PULONG ResultLength)
{
    ULONG Samples;
    ULONG NewIndex, OldIndex;

    Samples = BufferLength / (BitsPerSample / 8) / OldChannels;

    if (NewChannels > OldChannels)
    {
        if (BitsPerSample == 8)
        {
            PUCHAR BufferOut = ExAllocatePool(NonPagedPool, Samples * NewChannels);
            if (!BufferOut)
                return STATUS_INSUFFICIENT_RESOURCES;

            for(NewIndex = 0, OldIndex = 0; OldIndex < Samples * OldChannels; NewIndex += NewChannels, OldIndex += OldChannels)
            {
                ULONG SubIndex = 0;

                RtlMoveMemory(&BufferOut[NewIndex], &Buffer[OldIndex], OldChannels * sizeof(UCHAR));

                do
                {
                    /* 2 channel stretched to 4 looks like LRLR */
                     BufferOut[NewIndex+OldChannels + SubIndex] = Buffer[OldIndex + (SubIndex % OldChannels)];
                }while(SubIndex++ < NewChannels - OldChannels);
            }
            *Result = BufferOut;
            *ResultLength = Samples * NewChannels;
        }
        else if (BitsPerSample == 16)
        {
            PUSHORT BufferOut = ExAllocatePool(NonPagedPool, Samples * NewChannels);
            if (!BufferOut)
                return STATUS_INSUFFICIENT_RESOURCES;

            for(NewIndex = 0, OldIndex = 0; OldIndex < Samples * OldChannels; NewIndex += NewChannels, OldIndex += OldChannels)
            {
                ULONG SubIndex = 0;

                RtlMoveMemory(&BufferOut[NewIndex], &Buffer[OldIndex], OldChannels * sizeof(USHORT));

                do
                {
                     BufferOut[NewIndex+OldChannels + SubIndex] = Buffer[OldIndex + (SubIndex % OldChannels)];
                }while(SubIndex++ < NewChannels - OldChannels);
            }
            *Result = BufferOut;
            *ResultLength = Samples * NewChannels;
        }
        else if (BitsPerSample == 24)
        {
            PUCHAR BufferOut = ExAllocatePool(NonPagedPool, Samples * NewChannels);
            if (!BufferOut)
                return STATUS_INSUFFICIENT_RESOURCES;

            for(NewIndex = 0, OldIndex = 0; OldIndex < Samples * OldChannels; NewIndex += NewChannels, OldIndex += OldChannels)
            {
                ULONG SubIndex = 0;

                RtlMoveMemory(&BufferOut[NewIndex], &Buffer[OldIndex], OldChannels * 3);

                do
                {
                     RtlMoveMemory(&BufferOut[(NewIndex+OldChannels + SubIndex) * 3], &Buffer[(OldIndex + (SubIndex % OldChannels)) * 3], 3);
                }while(SubIndex++ < NewChannels - OldChannels);
            }
            *Result = BufferOut;
            *ResultLength = Samples * NewChannels;
        }
        else if (BitsPerSample == 32)
        {
            PULONG BufferOut = ExAllocatePool(NonPagedPool, Samples * NewChannels);
            if (!BufferOut)
                return STATUS_INSUFFICIENT_RESOURCES;

            for(NewIndex = 0, OldIndex = 0; OldIndex < Samples * OldChannels; NewIndex += NewChannels, OldIndex += OldChannels)
            {
                ULONG SubIndex = 0;

                RtlMoveMemory(&BufferOut[NewIndex], &Buffer[OldIndex], OldChannels * sizeof(ULONG));

                do
                {
                     BufferOut[NewIndex+OldChannels + SubIndex] = Buffer[OldIndex + (SubIndex % OldChannels)];
                }while(SubIndex++ < NewChannels - OldChannels);
            }
            *Result = BufferOut;
            *ResultLength = Samples * NewChannels;
        }

    }
    else
    {
        PUSHORT BufferOut = ExAllocatePool(NonPagedPool, Samples * NewChannels);
        if (!BufferOut)
            return STATUS_INSUFFICIENT_RESOURCES;

        for(NewIndex = 0, OldIndex = 0; OldIndex < Samples * OldChannels; NewIndex += NewChannels, OldIndex += OldChannels)
        {
            /* TODO
             * mix stream instead of just dumping part of it ;)
             */
            RtlMoveMemory(&BufferOut[NewIndex], &Buffer[OldIndex], NewChannels * (BitsPerSample/8));
        }

        *Result = BufferOut;
        *ResultLength = Samples * NewChannels;
    }
    return STATUS_SUCCESS;
}