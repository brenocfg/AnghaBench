#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  current; } ;
typedef  TYPE_1__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  esccheck (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lisxdigit (int /*<<< orphan*/ ) ; 
 int luaO_hexavalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_and_next (TYPE_1__*) ; 

__attribute__((used)) static int gethexa (LexState *ls) {
  save_and_next(ls);
  esccheck (ls, lisxdigit(ls->current), "hexadecimal digit expected");
  return luaO_hexavalue(ls->current);
}