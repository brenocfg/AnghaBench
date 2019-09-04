#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_4__ {scalar_t__ Size; } ;
typedef  TYPE_1__* PXMS_HANDLE ;

/* Variables and functions */
 TYPE_1__* HandleTable ; 
 int XMS_MAX_HANDLES ; 

__attribute__((used)) static inline PXMS_HANDLE GetXmsHandleRecord(WORD Handle)
{
    PXMS_HANDLE Entry;
    if (Handle == 0 || Handle >= XMS_MAX_HANDLES) return NULL;

    Entry = &HandleTable[Handle - 1];
    return Entry->Size ? Entry : NULL;
}