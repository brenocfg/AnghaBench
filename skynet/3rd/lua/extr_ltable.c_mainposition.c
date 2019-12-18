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
typedef  int /*<<< orphan*/  Table ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
#define  LUA_TBOOLEAN 134 
#define  LUA_TLCF 133 
#define  LUA_TLIGHTUSERDATA 132 
#define  LUA_TLNGSTR 131 
#define  LUA_TNUMFLT 130 
#define  LUA_TNUMINT 129 
#define  LUA_TSHRSTR 128 
 int /*<<< orphan*/  bvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fltvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gcvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * hashboolean (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hashint (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hashmod (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hashpointer (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hashpow2 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hashstr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  l_hashfloat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaS_hashlongstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  pvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tsvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ttisdeadkey (int /*<<< orphan*/  const*) ; 
 int ttype (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static Node *mainposition (const Table *t, const TValue *key) {
  switch (ttype(key)) {
    case LUA_TNUMINT:
      return hashint(t, ivalue(key));
    case LUA_TNUMFLT:
      return hashmod(t, l_hashfloat(fltvalue(key)));
    case LUA_TSHRSTR:
      return hashstr(t, tsvalue(key));
    case LUA_TLNGSTR:
      return hashpow2(t, luaS_hashlongstr(tsvalue(key)));
    case LUA_TBOOLEAN:
      return hashboolean(t, bvalue(key));
    case LUA_TLIGHTUSERDATA:
      return hashpointer(t, pvalue(key));
    case LUA_TLCF:
      return hashpointer(t, fvalue(key));
    default:
      lua_assert(!ttisdeadkey(key));
      return hashpointer(t, gcvalue(key));
  }
}