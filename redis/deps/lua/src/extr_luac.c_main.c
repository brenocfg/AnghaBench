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
struct Smain {int argc; char** argv; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int doargs (int,char**) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_cpcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct Smain*) ; 
 int /*<<< orphan*/ * lua_open () ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pmain ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char* argv[])
{
 lua_State* L;
 struct Smain s;
 int i=doargs(argc,argv);
 argc-=i; argv+=i;
 if (argc<=0) usage("no input files given");
 L=lua_open();
 if (L==NULL) fatal("not enough memory for state");
 s.argc=argc;
 s.argv=argv;
 if (lua_cpcall(L,pmain,&s)!=0) fatal(lua_tostring(L,-1));
 lua_close(L);
 return EXIT_SUCCESS;
}