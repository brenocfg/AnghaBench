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
typedef  int WORD ;
struct TYPE_5__ {TYPE_1__* Part; } ;
struct TYPE_4__ {int LowerLimit; int UpperLimit; } ;
typedef  TYPE_2__ IPADDRESS_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL IPADDRESS_SetRange (IPADDRESS_INFO *infoPtr, int index, WORD range)
{
    TRACE("\n");

    if ( (index < 0) || (index > 3) ) return FALSE;

    infoPtr->Part[index].LowerLimit = range & 0xFF;
    infoPtr->Part[index].UpperLimit = (range >> 8)  & 0xFF;

    return TRUE;
}