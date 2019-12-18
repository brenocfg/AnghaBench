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
struct RedisModule {int options; } ;
typedef  int /*<<< orphan*/  sds ;

/* Variables and functions */
 int REDISMODULE_OPTIONS_HANDLE_IO_ERRORS ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 int /*<<< orphan*/  sdstrim (int /*<<< orphan*/ ,char*) ; 

sds genModulesInfoStringRenderModuleOptions(struct RedisModule *module) {
    sds output = sdsnew("[");
    if (module->options & REDISMODULE_OPTIONS_HANDLE_IO_ERRORS)
        output = sdscat(output,"handle-io-errors|");
    output = sdstrim(output,"|");
    output = sdscat(output,"]");
    return output;
}