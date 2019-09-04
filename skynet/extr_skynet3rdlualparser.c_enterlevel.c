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
struct TYPE_4__ {int /*<<< orphan*/  nCcalls; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_5__ {int /*<<< orphan*/  fs; TYPE_1__* L; } ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  LUAI_MAXCCALLS ; 
 int /*<<< orphan*/  checklimit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void enterlevel (LexState *ls) {
  lua_State *L = ls->L;
  ++L->nCcalls;
  checklimit(ls->fs, L->nCcalls, LUAI_MAXCCALLS, "C levels");
}