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
struct skynet_config {int /*<<< orphan*/  profile; void* logservice; void* logger; void* daemon; void* bootstrap; void* harbor; void* module_path; void* thread; } ;
struct lua_State {int dummy; } ;

/* Variables and functions */
 int LUA_OK ; 
 int /*<<< orphan*/  _init_env (struct lua_State*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  load_config ; 
 int /*<<< orphan*/  luaL_initcodecache () ; 
 int luaL_loadbufferx (struct lua_State*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct lua_State* luaL_newstate () ; 
 int /*<<< orphan*/  luaL_openlibs (struct lua_State*) ; 
 int /*<<< orphan*/  lua_close (struct lua_State*) ; 
 int lua_pcall (struct lua_State*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (struct lua_State*,char const*) ; 
 char* lua_tostring (struct lua_State*,int) ; 
 int /*<<< orphan*/  optboolean (char*,int) ; 
 void* optint (char*,int) ; 
 void* optstring (char*,char*) ; 
 int /*<<< orphan*/  sigign () ; 
 int /*<<< orphan*/  skynet_env_init () ; 
 int /*<<< orphan*/  skynet_globalexit () ; 
 int /*<<< orphan*/  skynet_globalinit () ; 
 int /*<<< orphan*/  skynet_start (struct skynet_config*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[]) {
	const char * config_file = NULL ;
	if (argc > 1) {
		config_file = argv[1];
	} else {
		fprintf(stderr, "Need a config file. Please read skynet wiki : https://github.com/cloudwu/skynet/wiki/Config\n"
			"usage: skynet configfilename\n");
		return 1;
	}

	skynet_globalinit();
	skynet_env_init();

	sigign();

	struct skynet_config config;

#ifdef LUA_CACHELIB
	// init the lock of code cache
	luaL_initcodecache();
#endif

	struct lua_State *L = luaL_newstate();
	luaL_openlibs(L);	// link lua lib

	int err =  luaL_loadbufferx(L, load_config, strlen(load_config), "=[skynet config]", "t");
	assert(err == LUA_OK);
	lua_pushstring(L, config_file);

	err = lua_pcall(L, 1, 1, 0);
	if (err) {
		fprintf(stderr,"%s\n",lua_tostring(L,-1));
		lua_close(L);
		return 1;
	}
	_init_env(L);

	config.thread =  optint("thread",8);
	config.module_path = optstring("cpath","./cservice/?.so");
	config.harbor = optint("harbor", 1);
	config.bootstrap = optstring("bootstrap","snlua bootstrap");
	config.daemon = optstring("daemon", NULL);
	config.logger = optstring("logger", NULL);
	config.logservice = optstring("logservice", "logger");
	config.profile = optboolean("profile", 1);

	lua_close(L);

	skynet_start(&config);
	skynet_globalexit();

	return 0;
}