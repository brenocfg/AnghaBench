#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ULONG ;
struct TYPE_16__ {scalar_t__ QuadPart; } ;
struct TYPE_15__ {struct TYPE_15__* Flink; } ;
struct TYPE_13__ {scalar_t__ QuadPart; } ;
struct TYPE_14__ {TYPE_1__ FileOffset; } ;
typedef  TYPE_2__* PNOCC_BCB ;
typedef  TYPE_4__* PLIST_ENTRY ;
typedef  TYPE_5__* PLARGE_INTEGER ;

/* Variables and functions */
 scalar_t__ CACHE_STRIPE ; 
 TYPE_2__* CONTAINING_RECORD (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CcCacheSections ; 
 TYPE_2__* INVALID_CACHE ; 
 int /*<<< orphan*/  NOCC_BCB ; 
 int /*<<< orphan*/  ThisFileList ; 

ULONG
CcpFindMatchingMap(PLIST_ENTRY Head,
                   PLARGE_INTEGER FileOffset,
                   ULONG Length)
{
    PLIST_ENTRY Entry;
    //DPRINT("Find Matching Map: (%x) %x:%x\n", FileOffset->LowPart, Length);
    for (Entry = Head->Flink; Entry != Head; Entry = Entry->Flink)
    {
        //DPRINT("Link @%x\n", Entry);
        PNOCC_BCB Bcb = CONTAINING_RECORD(Entry, NOCC_BCB, ThisFileList);
        //DPRINT("Selected BCB %x #%x\n", Bcb, Bcb - CcCacheSections);
        //DPRINT("This File: %x:%x\n", Bcb->FileOffset.LowPart, Bcb->Length);
        if (FileOffset->QuadPart >= Bcb->FileOffset.QuadPart &&
            FileOffset->QuadPart < Bcb->FileOffset.QuadPart + CACHE_STRIPE)
        {
            //DPRINT("Found match at #%x\n", Bcb - CcCacheSections);
            return Bcb - CcCacheSections;
        }
    }

    //DPRINT("This region isn't mapped\n");

    return INVALID_CACHE;
}