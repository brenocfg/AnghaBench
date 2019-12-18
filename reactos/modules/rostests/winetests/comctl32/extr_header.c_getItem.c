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
struct TYPE_2__ {int /*<<< orphan*/  cchTextMax; int /*<<< orphan*/  pszText; int /*<<< orphan*/  mask; } ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ HDITEMA ;

/* Variables and functions */
 int /*<<< orphan*/  HDI_TEXT ; 
 int /*<<< orphan*/  HDM_GETITEMA ; 
 int /*<<< orphan*/  MAX_CHARS ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LONG getItem(HWND hdex, int idx, LPSTR textBuffer)
{
    HDITEMA hdItem;
    hdItem.mask         = HDI_TEXT;
    hdItem.pszText      = textBuffer;
    hdItem.cchTextMax   = MAX_CHARS;
    return SendMessageA(hdex, HDM_GETITEMA, idx, (LPARAM)&hdItem);
}