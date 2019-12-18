#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  state; int /*<<< orphan*/  weak; int /*<<< orphan*/  grayagain; int /*<<< orphan*/  gray; } ;
struct TYPE_12__ {TYPE_1__ gc; int /*<<< orphan*/  registrytv; } ;
typedef  TYPE_2__ global_State ;
struct TYPE_13__ {int /*<<< orphan*/  env; } ;

/* Variables and functions */
 int /*<<< orphan*/  GCSpropagate ; 
 int /*<<< orphan*/  gc_mark_gcroot (TYPE_2__*) ; 
 int /*<<< orphan*/  gc_markobj (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  gc_marktv (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* mainthread (TYPE_2__*) ; 
 int /*<<< orphan*/  setgcrefnull (int /*<<< orphan*/ ) ; 
 TYPE_3__* tabref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gc_mark_start(global_State *g)
{
  setgcrefnull(g->gc.gray);
  setgcrefnull(g->gc.grayagain);
  setgcrefnull(g->gc.weak);
  gc_markobj(g, mainthread(g));
  gc_markobj(g, tabref(mainthread(g)->env));
  gc_marktv(g, &g->registrytv);
  gc_mark_gcroot(g);
  g->gc.state = GCSpropagate;
}