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
typedef  char WCHAR ;
struct TYPE_6__ {TYPE_1__* Part; } ;
struct TYPE_5__ {int LowerLimit; int UpperLimit; int /*<<< orphan*/  EditHwnd; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ IPPART_INFO ;
typedef  TYPE_2__ IPADDRESS_INFO ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EN_CHANGE ; 
 int /*<<< orphan*/  IPADDRESS_Notify (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,int) ; 

__attribute__((used)) static LRESULT IPADDRESS_SetAddress (const IPADDRESS_INFO *infoPtr, DWORD ip_address)
{
    WCHAR buf[20];
    static const WCHAR fmt[] = { '%', 'd', 0 };
    int i;

    TRACE("\n");

    for (i = 3; i >= 0; i--) {
	const IPPART_INFO* part = &infoPtr->Part[i];
        int value = ip_address & 0xff;
	if ( (value >= part->LowerLimit) && (value <= part->UpperLimit) ) {
	    wsprintfW (buf, fmt, value);
	    SetWindowTextW (part->EditHwnd, buf);
	    IPADDRESS_Notify (infoPtr, EN_CHANGE);
        }
        ip_address >>= 8;
    }

    return TRUE;
}