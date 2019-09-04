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
struct TYPE_2__ {int fMask; int cx; int cxMinChild; int cxIdeal; int cyMinChild; int /*<<< orphan*/ * lpText; int /*<<< orphan*/  hwndChild; int /*<<< orphan*/  cbSize; } ;
typedef  TYPE_1__ REBARBANDINFOA ;
typedef  int /*<<< orphan*/ * LPCSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int MAX_PATH ; 
 int RBBIM_CHILD ; 
 int RBBIM_CHILDSIZE ; 
 int RBBIM_IDEALSIZE ; 
 int RBBIM_SIZE ; 
 int RBBIM_TEXT ; 
 int /*<<< orphan*/  RB_INSERTBANDA ; 
 int /*<<< orphan*/  REBARBANDINFOA_V6_SIZE ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_toolbar (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_band_w(HWND hRebar, LPCSTR lpszText, int cxMinChild, int cx, int cxIdeal)
{
    CHAR buffer[MAX_PATH];
    REBARBANDINFOA rbi;

    if (lpszText != NULL)
        strcpy(buffer, lpszText);
    rbi.cbSize = REBARBANDINFOA_V6_SIZE;
    rbi.fMask = RBBIM_SIZE | RBBIM_CHILDSIZE | RBBIM_CHILD | RBBIM_IDEALSIZE | RBBIM_TEXT;
    rbi.cx = cx;
    rbi.cxMinChild = cxMinChild;
    rbi.cxIdeal = cxIdeal;
    rbi.cyMinChild = 20;
    rbi.hwndChild = build_toolbar(1, hRebar);
    rbi.lpText = (lpszText ? buffer : NULL);
    SendMessageA(hRebar, RB_INSERTBANDA, -1, (LPARAM)&rbi);
}