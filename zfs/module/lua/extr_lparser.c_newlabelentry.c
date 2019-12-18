#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int line; int pc; int /*<<< orphan*/  nactvar; int /*<<< orphan*/ * name; } ;
struct TYPE_9__ {int n; TYPE_6__* arr; int /*<<< orphan*/  size; } ;
struct TYPE_8__ {TYPE_1__* fs; int /*<<< orphan*/  L; } ;
struct TYPE_7__ {int /*<<< orphan*/  nactvar; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_2__ LexState ;
typedef  TYPE_3__ Labellist ;

/* Variables and functions */
 int /*<<< orphan*/  Labeldesc ; 
 int /*<<< orphan*/  SHRT_MAX ; 
 int /*<<< orphan*/  luaM_growvector (int /*<<< orphan*/ ,TYPE_6__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int newlabelentry (LexState *ls, Labellist *l, TString *name,
                          int line, int pc) {
  int n = l->n;
  luaM_growvector(ls->L, l->arr, n, l->size,
                  Labeldesc, SHRT_MAX, "labels/gotos");
  l->arr[n].name = name;
  l->arr[n].line = line;
  l->arr[n].nactvar = ls->fs->nactvar;
  l->arr[n].pc = pc;
  l->n++;
  return n;
}