#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  LexState ;

/* Variables and functions */
 int /*<<< orphan*/  luaX_newstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  new_localvar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void new_localvarliteral_ (LexState *ls, const char *name, size_t sz) {
  new_localvar(ls, luaX_newstring(ls, name, sz));
}