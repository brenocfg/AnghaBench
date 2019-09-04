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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/  seed; } ;
typedef  TYPE_1__ global_State ;
struct TYPE_5__ {scalar_t__ n; } ;
typedef  int /*<<< orphan*/  TString ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DEC (scalar_t__*) ; 
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 TYPE_2__ SSM ; 
 int /*<<< orphan*/ * add_string (unsigned int,char const*,size_t) ; 
 int /*<<< orphan*/ * addshrstr (int /*<<< orphan*/ *,char const*,size_t,unsigned int) ; 
 unsigned int luaS_hash (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * query_string (int /*<<< orphan*/ *,unsigned int,char const*,size_t) ; 
 int /*<<< orphan*/ * queryshrstr (int /*<<< orphan*/ *,char const*,size_t,unsigned int) ; 

__attribute__((used)) static TString *
internshrstr (lua_State *L, const char *str, size_t l) {
  TString *ts;
  global_State *g = G(L);
  unsigned int h = luaS_hash(str, l, g->seed);
  unsigned int h0;
  // lookup global state of this L first
  ts = queryshrstr (L, str, l, h);
  if (ts)
    return ts;
  // lookup SSM again
  h0 = luaS_hash(str, l, 0);
  ts = query_string(NULL, h0, str, l);
  if (ts)
    return ts;
  // If SSM.n greate than 0, add it to SSM
  if (SSM.n > 0) {
    ATOM_DEC(&SSM.n);
    return add_string(h0, str, l);
  }
  // Else add it to global state (local)
  return addshrstr (L, str, l, h);
}