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
struct TYPE_5__ {int type; int shift; int ctrl; int alt; int key; scalar_t__ dy; scalar_t__ dx; int /*<<< orphan*/  my; int /*<<< orphan*/  mx; } ;
typedef  TYPE_1__ stbwingraph_event ;
struct TYPE_6__ {int /*<<< orphan*/  my; int /*<<< orphan*/  mx; } ;
typedef  TYPE_2__ stbwingraph__window ;
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 scalar_t__ GetKeyState (int /*<<< orphan*/ ) ; 
 int MK_CONTROL ; 
 int MK_SHIFT ; 
 int /*<<< orphan*/  VK_MENU ; 

__attribute__((used)) static void stbwingraph__mousewheel(stbwingraph_event *e, int type, WPARAM wparam, LPARAM lparam, int capture, void *wnd, stbwingraph__window *z)
{
   // lparam seems bogus!
   static int captured = 0;
   e->type = type;
   if (z) {
      e->mx = z->mx;
      e->my = z->my;
   }
   e->dx = e->dy = 0;
   e->shift = (wparam & MK_SHIFT) != 0;
   e->ctrl  = (wparam & MK_CONTROL) != 0;
   e->alt   = (GetKeyState(VK_MENU)    < 0);
   e->key = ((int) wparam >> 16);
}