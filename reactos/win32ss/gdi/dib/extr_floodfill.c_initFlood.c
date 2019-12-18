#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_6__ {int /*<<< orphan*/ * floodStart; int /*<<< orphan*/ * floodData; } ;
struct TYPE_5__ {int right; int left; int bottom; int top; } ;
typedef  TYPE_1__ RECTL ;
typedef  int /*<<< orphan*/  FLOODITEM ;
typedef  TYPE_2__ FLOODINFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  TAG_DIB ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static __inline BOOL initFlood(FLOODINFO *info, RECTL *DstRect)
{
  ULONG width = DstRect->right - DstRect->left;
  ULONG height = DstRect->bottom - DstRect->top;
  info->floodData = ExAllocatePoolWithTag(NonPagedPool, width * height * sizeof(FLOODITEM), TAG_DIB); 
  if (info->floodData == NULL)
  {
    return FALSE;
  }
  info->floodStart = info->floodData + (width * height);
  DPRINT("Allocated flood stack from %p to %p\n", info->floodData, info->floodStart);
  return TRUE;
}