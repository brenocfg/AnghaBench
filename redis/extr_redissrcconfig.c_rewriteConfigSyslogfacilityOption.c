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
struct rewriteConfigState {int dummy; } ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_2__ {int syslog_facility; } ;

/* Variables and functions */
 int LOG_LOCAL0 ; 
 char* configEnumGetNameOrUnknown (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rewriteConfigRewriteLine (struct rewriteConfigState*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  sdsempty () ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  syslog_facility_enum ; 

void rewriteConfigSyslogfacilityOption(struct rewriteConfigState *state) {
    int value = server.syslog_facility;
    int force = value != LOG_LOCAL0;
    const char *name = NULL, *option = "syslog-facility";
    sds line;

    name = configEnumGetNameOrUnknown(syslog_facility_enum,value);
    line = sdscatprintf(sdsempty(),"%s %s",option,name);
    rewriteConfigRewriteLine(state,option,line,force);
}