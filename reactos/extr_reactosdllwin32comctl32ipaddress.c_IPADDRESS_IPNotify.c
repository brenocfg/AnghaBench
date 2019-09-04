#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  Notify; int /*<<< orphan*/  Self; } ;
struct TYPE_5__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; int /*<<< orphan*/  hwndFrom; } ;
struct TYPE_6__ {void* iValue; TYPE_1__ hdr; void* iField; } ;
typedef  TYPE_2__ NMIPADDRESS ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_3__ IPADDRESS_INFO ;
typedef  void* INT ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPN_FIELDCHANGED ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,void*,...) ; 
 int /*<<< orphan*/  WM_NOTIFY ; 

__attribute__((used)) static INT IPADDRESS_IPNotify (const IPADDRESS_INFO *infoPtr, INT field, INT value)
{
    NMIPADDRESS nmip;

    TRACE("(field=%x, value=%d)\n", field, value);

    nmip.hdr.hwndFrom = infoPtr->Self;
    nmip.hdr.idFrom   = GetWindowLongPtrW (infoPtr->Self, GWLP_ID);
    nmip.hdr.code     = IPN_FIELDCHANGED;

    nmip.iField = field;
    nmip.iValue = value;

    SendMessageW (infoPtr->Notify, WM_NOTIFY, nmip.hdr.idFrom, (LPARAM)&nmip);

    TRACE("<-- %d\n", nmip.iValue);

    return nmip.iValue;
}