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
struct TYPE_6__ {int cbSize; int /*<<< orphan*/  fMask; scalar_t__ himl; } ;
struct TYPE_5__ {scalar_t__ himl; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  int /*<<< orphan*/  REBARINFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__* LPREBARINFO ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RBIM_IMAGELIST ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
REBAR_GetBarInfo (const REBAR_INFO *infoPtr, LPREBARINFO lpInfo)
{
    if (!lpInfo || lpInfo->cbSize < sizeof (REBARINFO))
	return FALSE;

    TRACE("getting bar info!\n");

    if (infoPtr->himl) {
	lpInfo->himl = infoPtr->himl;
	lpInfo->fMask |= RBIM_IMAGELIST;
    }

    return TRUE;
}