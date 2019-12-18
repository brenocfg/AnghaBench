#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  void* StkId ;

/* Variables and functions */
#define  LUA_MULTRET 128 
 int /*<<< orphan*/ * luaO_nilobject ; 
 int /*<<< orphan*/  setnilvalue (void*) ; 
 int /*<<< orphan*/  setobjs2s (TYPE_1__*,void*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int moveresults (lua_State *L, const TValue *firstResult, StkId res,
                                      int nres, int wanted) {
  switch (wanted) {  /* handle typical cases separately */
    case 0: break;  /* nothing to move */
    case 1: {  /* one result needed */
      if (nres == 0)   /* no results? */
        firstResult = luaO_nilobject;  /* adjust with nil */
      setobjs2s(L, res, firstResult);  /* move it to proper place */
      break;
    }
    case LUA_MULTRET: {
      int i;
      for (i = 0; i < nres; i++)  /* move all results to correct place */
        setobjs2s(L, res + i, firstResult + i);
      L->top = res + nres;
      return 0;  /* wanted == LUA_MULTRET */
    }
    default: {
      int i;
      if (wanted <= nres) {  /* enough results? */
        for (i = 0; i < wanted; i++)  /* move wanted results to correct place */
          setobjs2s(L, res + i, firstResult + i);
      }
      else {  /* not enough results; use all of them plus nils */
        for (i = 0; i < nres; i++)  /* move all results to correct place */
          setobjs2s(L, res + i, firstResult + i);
        for (; i < wanted; i++)  /* complete wanted number of results */
          setnilvalue(res + i);
      }
      break;
    }
  }
  L->top = res + wanted;  /* top points after the last result */
  return 1;
}