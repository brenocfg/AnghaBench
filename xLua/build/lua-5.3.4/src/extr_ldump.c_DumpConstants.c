#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sizek; int /*<<< orphan*/ * k; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ Proto ;
typedef  int /*<<< orphan*/  DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  DumpByte (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpInt (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpInteger (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpNumber (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpString (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  LUA_TBOOLEAN 133 
#define  LUA_TLNGSTR 132 
#define  LUA_TNIL 131 
#define  LUA_TNUMFLT 130 
#define  LUA_TNUMINT 129 
#define  LUA_TSHRSTR 128 
 int bvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fltvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ivalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsvalue (int /*<<< orphan*/  const*) ; 
 int ttype (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void DumpConstants (const Proto *f, DumpState *D) {
  int i;
  int n = f->sizek;
  DumpInt(n, D);
  for (i = 0; i < n; i++) {
    const TValue *o = &f->k[i];
    DumpByte(ttype(o), D);
    switch (ttype(o)) {
    case LUA_TNIL:
      break;
    case LUA_TBOOLEAN:
      DumpByte(bvalue(o), D);
      break;
    case LUA_TNUMFLT:
      DumpNumber(fltvalue(o), D);
      break;
    case LUA_TNUMINT:
      DumpInteger(ivalue(o), D);
      break;
    case LUA_TSHRSTR:
    case LUA_TLNGSTR:
      DumpString(tsvalue(o), D);
      break;
    default:
      lua_assert(0);
    }
  }
}