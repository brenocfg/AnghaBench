#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mask; int cxy; scalar_t__ cchTextMax; int /*<<< orphan*/  pszText; } ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ HDITEMA ;

/* Variables and functions */
 int HDI_TEXT ; 
 int HDI_WIDTH ; 
 int /*<<< orphan*/  HDM_INSERTITEMA ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LONG addItem(HWND hdex, int idx, LPSTR text)
{
    HDITEMA hdItem;
    hdItem.mask       = HDI_TEXT | HDI_WIDTH;
    hdItem.cxy        = 100;
    hdItem.pszText    = text;
    hdItem.cchTextMax = 0;
    return SendMessageA(hdex, HDM_INSERTITEMA, idx, (LPARAM)&hdItem);
}