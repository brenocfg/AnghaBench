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
struct TYPE_2__ {int member_0; int member_1; int x; int y; } ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  EM_GETSCROLLPOS ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int,int) ; 

__attribute__((used)) static int get_scroll_pos_y(HWND hwnd)
{
  POINT p = {-1, -1};
  SendMessageA(hwnd, EM_GETSCROLLPOS, 0, (LPARAM)&p);
  ok(p.x != -1 && p.y != -1, "p.x:%d p.y:%d\n", p.x, p.y);
  return p.y;
}