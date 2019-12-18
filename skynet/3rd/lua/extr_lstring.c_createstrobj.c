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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {unsigned int hash; scalar_t__ id; scalar_t__ extra; } ;
typedef  TYPE_1__ TString ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_1__* gco2ts (int /*<<< orphan*/ *) ; 
 char* getstr (TYPE_1__*) ; 
 int /*<<< orphan*/ * luaC_newobj (int /*<<< orphan*/ *,int,size_t) ; 
 size_t sizelstring (size_t) ; 

__attribute__((used)) static TString *createstrobj (lua_State *L, size_t l, int tag, unsigned int h) {
  TString *ts;
  GCObject *o;
  size_t totalsize;  /* total size of TString object */
  totalsize = sizelstring(l);
  o = luaC_newobj(L, tag, totalsize);
  ts = gco2ts(o);
  ts->hash = h;
  ts->extra = 0;
  ts->id = 0;
  getstr(ts)[l] = '\0';  /* ending 0 */
  return ts;
}