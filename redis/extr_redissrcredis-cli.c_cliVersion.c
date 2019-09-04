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
typedef  int /*<<< orphan*/  sds ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_VERSION ; 
 int /*<<< orphan*/  redisGitDirty () ; 
 int /*<<< orphan*/  redisGitSHA1 () ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sdsempty () ; 
 scalar_t__ strtoll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static sds cliVersion(void) {
    sds version;
    version = sdscatprintf(sdsempty(), "%s", REDIS_VERSION);

    /* Add git commit and working tree status when available */
    if (strtoll(redisGitSHA1(),NULL,16)) {
        version = sdscatprintf(version, " (git:%s", redisGitSHA1());
        if (strtoll(redisGitDirty(),NULL,10))
            version = sdscatprintf(version, "-dirty");
        version = sdscat(version, ")");
    }
    return version;
}