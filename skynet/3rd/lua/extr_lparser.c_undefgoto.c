#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  l_noret ;
struct TYPE_7__ {int /*<<< orphan*/  line; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ LexState ;
typedef  TYPE_2__ Labeldesc ;

/* Variables and functions */
 int /*<<< orphan*/  getstr (int /*<<< orphan*/ ) ; 
 scalar_t__ isreserved (int /*<<< orphan*/ ) ; 
 char* luaO_pushfstring (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  semerror (TYPE_1__*,char const*) ; 

__attribute__((used)) static l_noret undefgoto (LexState *ls, Labeldesc *gt) {
  const char *msg = isreserved(gt->name)
                    ? "<%s> at line %d not inside a loop"
                    : "no visible label '%s' for <goto> at line %d";
  msg = luaO_pushfstring(ls->L, msg, getstr(gt->name), gt->line);
  semerror(ls, msg);
}