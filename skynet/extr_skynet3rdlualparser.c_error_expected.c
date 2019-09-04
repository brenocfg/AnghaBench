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
typedef  int /*<<< orphan*/  l_noret ;
struct TYPE_5__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  luaO_pushfstring (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaX_syntaxerror (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaX_token2str (TYPE_1__*,int) ; 

__attribute__((used)) static l_noret error_expected (LexState *ls, int token) {
  luaX_syntaxerror(ls,
      luaO_pushfstring(ls->L, "%s expected", luaX_token2str(ls, token)));
}