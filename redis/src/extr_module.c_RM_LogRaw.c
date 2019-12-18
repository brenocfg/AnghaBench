#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_5__ {int verbosity; } ;
struct TYPE_4__ {char* name; } ;
typedef  TYPE_1__ RedisModule ;

/* Variables and functions */
 int LL_DEBUG ; 
 int LL_NOTICE ; 
 int LL_VERBOSE ; 
 int LL_WARNING ; 
 int LOG_MAX_LEN ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverLogRaw (int,char*) ; 
 size_t snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

void RM_LogRaw(RedisModule *module, const char *levelstr, const char *fmt, va_list ap) {
    char msg[LOG_MAX_LEN];
    size_t name_len;
    int level;

    if (!strcasecmp(levelstr,"debug")) level = LL_DEBUG;
    else if (!strcasecmp(levelstr,"verbose")) level = LL_VERBOSE;
    else if (!strcasecmp(levelstr,"notice")) level = LL_NOTICE;
    else if (!strcasecmp(levelstr,"warning")) level = LL_WARNING;
    else level = LL_VERBOSE; /* Default. */

    if (level < server.verbosity) return;

    name_len = snprintf(msg, sizeof(msg),"<%s> ", module? module->name: "module");
    vsnprintf(msg + name_len, sizeof(msg) - name_len, fmt, ap);
    serverLogRaw(level,msg);
}