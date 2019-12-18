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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {char* (* reader ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ;size_t n; char const* p; int /*<<< orphan*/  data; int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ ZIO ;

/* Variables and functions */
 int EOZ ; 
 int cast_uchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_unlock (int /*<<< orphan*/ *) ; 
 char* stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 

int luaZ_fill (ZIO *z) {
  size_t size;
  lua_State *L = z->L;
  const char *buff;
  lua_unlock(L);
  buff = z->reader(L, z->data, &size);
  lua_lock(L);
  if (buff == NULL || size == 0)
    return EOZ;
  z->n = size - 1;  /* discount char being returned */
  z->p = buff;
  return cast_uchar(*(z->p++));
}