#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ nCount; } ;
struct TYPE_7__ {TYPE_1__ rdh; } ;
typedef  TYPE_2__ RGNDATA ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetRegionData (int /*<<< orphan*/ ,scalar_t__,TYPE_2__*) ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static DWORD rgn_rect_count(HRGN hrgn)
{
    DWORD size;
    RGNDATA *data;

    if (!hrgn) return 0;
    if (!(size = GetRegionData(hrgn, 0, NULL))) return 0;
    if (!(data = HeapAlloc(GetProcessHeap(), 0, size))) return 0;
    GetRegionData(hrgn, size, data);
    size = data->rdh.nCount;
    HeapFree(GetProcessHeap(), 0, data);
    return size;
}