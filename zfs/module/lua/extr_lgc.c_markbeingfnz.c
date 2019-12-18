#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * tobefnz; } ;
typedef  TYPE_1__ global_State ;
struct TYPE_7__ {int /*<<< orphan*/ * next; } ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_5__* gch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makewhite (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reallymarkobject (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void markbeingfnz (global_State *g) {
  GCObject *o;
  for (o = g->tobefnz; o != NULL; o = gch(o)->next) {
    makewhite(g, o);
    reallymarkobject(g, o);
  }
}