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
struct TYPE_5__ {int cxy; int /*<<< orphan*/  mask; } ;
struct TYPE_4__ {int* widths; int /*<<< orphan*/  hwndHeader; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ Pane ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_2__ HDITEMW ;

/* Variables and functions */
 int COLUMNS ; 
 int GetScrollPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDI_WIDTH ; 
 int /*<<< orphan*/  HDM_SETITEMW ; 
 int /*<<< orphan*/  SB_HORZ ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_header(Pane* pane)
{
	HDITEMW item;
	int scroll_pos = GetScrollPos(pane->hwnd, SB_HORZ);
	int i=0, x=0;

	item.mask = HDI_WIDTH;
	item.cxy = 0;

	for(; (i < COLUMNS) && (x+pane->widths[i] < scroll_pos); i++) {
		x += pane->widths[i];
		SendMessageW(pane->hwndHeader, HDM_SETITEMW, i, (LPARAM)&item);
	}

	if (i < COLUMNS) {
		x += pane->widths[i];
		item.cxy = x - scroll_pos;
		SendMessageW(pane->hwndHeader, HDM_SETITEMW, i++, (LPARAM)&item);

		for(; i < COLUMNS; i++) {
			item.cxy = pane->widths[i];
			x += pane->widths[i];
			SendMessageW(pane->hwndHeader, HDM_SETITEMW, i, (LPARAM)&item);
		}
	}
}