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
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdscatrepr (int /*<<< orphan*/ ,char*,long long) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  string2ll (char*,int,long long*) ; 

char *ldbRedisProtocolToHuman_Bulk(sds *o, char *reply) {
    char *p = strchr(reply+1,'\r');
    long long bulklen;

    string2ll(reply+1,p-reply-1,&bulklen);
    if (bulklen == -1) {
        *o = sdscatlen(*o,"NULL",4);
        return p+2;
    } else {
        *o = sdscatrepr(*o,p+2,bulklen);
        return p+2+bulklen+2;
    }
}