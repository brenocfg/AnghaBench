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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  TTree ;
typedef  int /*<<< orphan*/  Pattern ;

/* Variables and functions */
 int lua_rawlen (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int getsize (lua_State *L, int idx) {
  return (lua_rawlen(L, idx) - sizeof(Pattern)) / sizeof(TTree) + 1;
}