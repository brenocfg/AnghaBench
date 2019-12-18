#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int argc; char** argv; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  l_message (char*,char*) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int lua_cpcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lua_open () ; 
 int /*<<< orphan*/  pmain ; 
 int /*<<< orphan*/  report (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ smain ; 

int main(int argc, char **argv)
{
  int status;
  lua_State *L = lua_open();
  if (L == NULL) {
    l_message(argv[0], "cannot create state: not enough memory");
    return EXIT_FAILURE;
  }
  smain.argc = argc;
  smain.argv = argv;
  status = lua_cpcall(L, pmain, NULL);
  report(L, status);
  lua_close(L);
  return (status || smain.status > 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}