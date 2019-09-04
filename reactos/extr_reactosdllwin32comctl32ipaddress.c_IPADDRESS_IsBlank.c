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
struct TYPE_5__ {TYPE_1__* Part; } ;
struct TYPE_4__ {int /*<<< orphan*/  EditHwnd; } ;
typedef  TYPE_2__ IPADDRESS_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetWindowTextLengthW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL IPADDRESS_IsBlank (const IPADDRESS_INFO *infoPtr)
{
    int i;

    TRACE("\n");

    for (i = 0; i < 4; i++)
        if (GetWindowTextLengthW (infoPtr->Part[i].EditHwnd)) return FALSE;

    return TRUE;
}