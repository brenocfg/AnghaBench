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
struct TYPE_5__ {int type; int key; int shift; int ctrl; int alt; scalar_t__ dy; scalar_t__ dx; scalar_t__ my; scalar_t__ mx; } ;
typedef  TYPE_1__ stbwingraph_event ;
struct TYPE_6__ {scalar_t__ my; scalar_t__ mx; } ;
typedef  TYPE_2__ stbwingraph__window ;

/* Variables and functions */
 scalar_t__ GetKeyState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VK_CONTROL ; 
 int /*<<< orphan*/  VK_MENU ; 
 int /*<<< orphan*/  VK_SHIFT ; 

__attribute__((used)) static void stbwingraph__key(stbwingraph_event *e, int type, int key, stbwingraph__window *z)
{
   e->type  = type;
   e->key   = key;
   e->shift = (GetKeyState(VK_SHIFT)   < 0);
   e->ctrl  = (GetKeyState(VK_CONTROL) < 0);
   e->alt   = (GetKeyState(VK_MENU)    < 0);
   if  (z) {
      e->mx    = z->mx;
      e->my    = z->my;
   } else {
      e->mx = e->my = 0;
   }
   e->dx = e->dy = 0;
}