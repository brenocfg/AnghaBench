#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ VarInfo ;
struct TYPE_11__ {int vtop; TYPE_3__* vstack; TYPE_2__* fs; } ;
struct TYPE_9__ {TYPE_1__* bl; } ;
struct TYPE_8__ {int vstart; } ;
typedef  TYPE_4__ LexState ;
typedef  int /*<<< orphan*/  GCstr ;

/* Variables and functions */
 scalar_t__ gola_islabel (TYPE_3__*) ; 
 int /*<<< orphan*/ * strref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VarInfo *gola_findlabel(LexState *ls, GCstr *name)
{
  VarInfo *v = ls->vstack + ls->fs->bl->vstart;
  VarInfo *ve = ls->vstack + ls->vtop;
  for (; v < ve; v++)
    if (strref(v->name) == name && gola_islabel(v))
      return v;
  return NULL;
}