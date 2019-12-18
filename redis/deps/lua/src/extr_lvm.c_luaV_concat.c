#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_14__ {int base; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_15__ {size_t len; } ;
struct TYPE_13__ {int /*<<< orphan*/  buff; } ;
typedef  int StkId ;

/* Variables and functions */
 TYPE_11__* G (TYPE_1__*) ; 
 size_t MAX_SIZET ; 
 int /*<<< orphan*/  TM_CONCAT ; 
 int /*<<< orphan*/  call_binTM (TYPE_1__*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaG_concaterror (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  luaG_runerror (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  luaS_newlstr (TYPE_1__*,char*,size_t) ; 
 char* luaZ_openspace (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  setsvalue2s (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svalue (int) ; 
 scalar_t__ tostring (TYPE_1__*,int) ; 
 TYPE_2__* tsvalue (int) ; 
 scalar_t__ ttisnumber (int) ; 
 scalar_t__ ttisstring (int) ; 

void luaV_concat (lua_State *L, int total, int last) {
  do {
    StkId top = L->base + last + 1;
    int n = 2;  /* number of elements handled in this pass (at least 2) */
    if (!(ttisstring(top-2) || ttisnumber(top-2)) || !tostring(L, top-1)) {
      if (!call_binTM(L, top-2, top-1, top-2, TM_CONCAT))
        luaG_concaterror(L, top-2, top-1);
    } else if (tsvalue(top-1)->len == 0)  /* second op is empty? */
      (void)tostring(L, top - 2);  /* result is first op (as string) */
    else {
      /* at least two string values; get as many as possible */
      size_t tl = tsvalue(top-1)->len;
      char *buffer;
      int i;
      /* collect total length */
      for (n = 1; n < total && tostring(L, top-n-1); n++) {
        size_t l = tsvalue(top-n-1)->len;
        if (l >= MAX_SIZET - tl) luaG_runerror(L, "string length overflow");
        tl += l;
      }
      buffer = luaZ_openspace(L, &G(L)->buff, tl);
      tl = 0;
      for (i=n; i>0; i--) {  /* concat all strings */
        size_t l = tsvalue(top-i)->len;
        memcpy(buffer+tl, svalue(top-i), l);
        tl += l;
      }
      setsvalue2s(L, top-n, luaS_newlstr(L, buffer, tl));
    }
    total -= n-1;  /* got `n' strings to create 1 new */
    last -= n-1;
  } while (total > 1);  /* repeat until only 1 result left */
}