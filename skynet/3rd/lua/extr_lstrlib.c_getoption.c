#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  lua_Integer ;
struct TYPE_6__ {int little; } ;
struct TYPE_5__ {int islittle; int /*<<< orphan*/  L; void* maxalign; } ;
typedef  int /*<<< orphan*/  KOption ;
typedef  TYPE_1__ Header ;

/* Variables and functions */
 int /*<<< orphan*/  Kchar ; 
 int /*<<< orphan*/  Kfloat ; 
 int /*<<< orphan*/  Kint ; 
 int /*<<< orphan*/  Knop ; 
 int /*<<< orphan*/  Kpaddalign ; 
 int /*<<< orphan*/  Kpadding ; 
 int /*<<< orphan*/  Kstring ; 
 int /*<<< orphan*/  Kuint ; 
 int /*<<< orphan*/  Kzstr ; 
 int MAXALIGN ; 
 int getnum (char const**,int) ; 
 void* getnumlimit (TYPE_1__*,char const**,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__ nativeendian ; 

__attribute__((used)) static KOption getoption (Header *h, const char **fmt, int *size) {
  int opt = *((*fmt)++);
  *size = 0;  /* default */
  switch (opt) {
    case 'b': *size = sizeof(char); return Kint;
    case 'B': *size = sizeof(char); return Kuint;
    case 'h': *size = sizeof(short); return Kint;
    case 'H': *size = sizeof(short); return Kuint;
    case 'l': *size = sizeof(long); return Kint;
    case 'L': *size = sizeof(long); return Kuint;
    case 'j': *size = sizeof(lua_Integer); return Kint;
    case 'J': *size = sizeof(lua_Integer); return Kuint;
    case 'T': *size = sizeof(size_t); return Kuint;
    case 'f': *size = sizeof(float); return Kfloat;
    case 'd': *size = sizeof(double); return Kfloat;
    case 'n': *size = sizeof(lua_Number); return Kfloat;
    case 'i': *size = getnumlimit(h, fmt, sizeof(int)); return Kint;
    case 'I': *size = getnumlimit(h, fmt, sizeof(int)); return Kuint;
    case 's': *size = getnumlimit(h, fmt, sizeof(size_t)); return Kstring;
    case 'c':
      *size = getnum(fmt, -1);
      if (*size == -1)
        luaL_error(h->L, "missing size for format option 'c'");
      return Kchar;
    case 'z': return Kzstr;
    case 'x': *size = 1; return Kpadding;
    case 'X': return Kpaddalign;
    case ' ': break;
    case '<': h->islittle = 1; break;
    case '>': h->islittle = 0; break;
    case '=': h->islittle = nativeendian.little; break;
    case '!': h->maxalign = getnumlimit(h, fmt, MAXALIGN); break;
    default: luaL_error(h->L, "invalid format option '%c'", opt);
  }
  return Knop;
}