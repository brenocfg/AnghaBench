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
struct TYPE_2__ {void* cpMin; void* cpMax; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  void* LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ CHARRANGE ;

/* Variables and functions */
 int /*<<< orphan*/  EM_EXSETSEL ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void move_cursor(HWND hwnd, LONG charindex)
{
  CHARRANGE cr;
  cr.cpMax = charindex;
  cr.cpMin = charindex;
  SendMessageA(hwnd, EM_EXSETSEL, 0, (LPARAM)&cr);
}