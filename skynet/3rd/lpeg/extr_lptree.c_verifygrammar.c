#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_9__ {scalar_t__ tag; scalar_t__ key; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
 int MAXRULES ; 
 scalar_t__ TRule ; 
 scalar_t__ TTrue ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ checkloops (TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,scalar_t__) ; 
 TYPE_1__* sib1 (TYPE_1__*) ; 
 TYPE_1__* sib2 (TYPE_1__*) ; 
 int /*<<< orphan*/  val2str (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  verifyrule (int /*<<< orphan*/ *,TYPE_1__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void verifygrammar (lua_State *L, TTree *grammar) {
  int passed[MAXRULES];
  TTree *rule;
  /* check left-recursive rules */
  for (rule = sib1(grammar); rule->tag == TRule; rule = sib2(rule)) {
    if (rule->key == 0) continue;  /* unused rule */
    verifyrule(L, sib1(rule), passed, 0, 0);
  }
  assert(rule->tag == TTrue);
  /* check infinite loops inside rules */
  for (rule = sib1(grammar); rule->tag == TRule; rule = sib2(rule)) {
    if (rule->key == 0) continue;  /* unused rule */
    if (checkloops(sib1(rule))) {
      lua_rawgeti(L, -1, rule->key);  /* get rule's key */
      luaL_error(L, "empty loop in rule '%s'", val2str(L, -1));
    }
  }
  assert(rule->tag == TTrue);
}