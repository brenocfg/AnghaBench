#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct listbox_stat {void* selcount; void* caret; void* anchor; void* selected; } ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  LB_GETANCHORINDEX ; 
 int /*<<< orphan*/  LB_GETCARETINDEX ; 
 int /*<<< orphan*/  LB_GETCURSEL ; 
 int /*<<< orphan*/  LB_GETSELCOUNT ; 
 void* SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
listbox_query (HWND handle, struct listbox_stat *results)
{
  results->selected = SendMessageA(handle, LB_GETCURSEL, 0, 0);
  results->anchor   = SendMessageA(handle, LB_GETANCHORINDEX, 0, 0);
  results->caret    = SendMessageA(handle, LB_GETCARETINDEX, 0, 0);
  results->selcount = SendMessageA(handle, LB_GETSELCOUNT, 0, 0);
}