#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  Self; TYPE_1__* Part; int /*<<< orphan*/  Enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  EditHwnd; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__ IPADDRESS_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InvalidateRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT IPADDRESS_Enable (IPADDRESS_INFO *infoPtr, BOOL enabled)
{
    int i;

    infoPtr->Enabled = enabled;

    for (i = 0; i < 4; i++)
        EnableWindow(infoPtr->Part[i].EditHwnd, enabled);

    InvalidateRgn(infoPtr->Self, NULL, FALSE);
    return 0;
}