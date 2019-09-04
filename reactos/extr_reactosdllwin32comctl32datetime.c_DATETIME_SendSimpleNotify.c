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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/  hwndNotify; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_4__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; int /*<<< orphan*/  hwndFrom; } ;
typedef  TYPE_1__ NMHDR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_2__ DATETIME_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NOTIFY ; 

__attribute__((used)) static BOOL
DATETIME_SendSimpleNotify (const DATETIME_INFO *infoPtr, UINT code)
{
    NMHDR nmhdr;

    TRACE("%x\n", code);
    nmhdr.hwndFrom = infoPtr->hwndSelf;
    nmhdr.idFrom   = GetWindowLongPtrW(infoPtr->hwndSelf, GWLP_ID);
    nmhdr.code     = code;

    return (BOOL) SendMessageW (infoPtr->hwndNotify, WM_NOTIFY,
                                nmhdr.idFrom, (LPARAM)&nmhdr);
}