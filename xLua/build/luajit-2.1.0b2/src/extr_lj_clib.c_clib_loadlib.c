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

/* Variables and functions */
 int RTLD_GLOBAL ; 
 int RTLD_LAZY ; 
 int RTLD_LOCAL ; 
 char const* clib_extname (int /*<<< orphan*/ *,char const*) ; 
 char* clib_resolve_lds (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* dlerror () ; 
 void* dlopen (char const*,int) ; 
 int /*<<< orphan*/  lj_err_callermsg (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lj_str_new (int /*<<< orphan*/ *,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *clib_loadlib(lua_State *L, const char *name, int global)
{
  void *h = dlopen(clib_extname(L, name),
		   RTLD_LAZY | (global?RTLD_GLOBAL:RTLD_LOCAL));
  if (!h) {
    const char *e, *err = dlerror();
    if (*err == '/' && (e = strchr(err, ':')) &&
	(name = clib_resolve_lds(L, strdata(lj_str_new(L, err, e-err))))) {
      h = dlopen(name, RTLD_LAZY | (global?RTLD_GLOBAL:RTLD_LOCAL));
      if (h) return h;
      err = dlerror();
    }
    lj_err_callermsg(L, err);
  }
  return h;
}