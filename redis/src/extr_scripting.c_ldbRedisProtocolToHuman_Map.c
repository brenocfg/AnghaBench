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
 char* ldbRedisProtocolToHuman (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  string2ll (char*,int,long long*) ; 

char *ldbRedisProtocolToHuman_Map(sds *o, char *reply) {
    char *p = strchr(reply+1,'\r');
    long long mbulklen;
    int j = 0;

    string2ll(reply+1,p-reply-1,&mbulklen);
    p += 2;
    *o = sdscatlen(*o,"{",1);
    for (j = 0; j < mbulklen; j++) {
        p = ldbRedisProtocolToHuman(o,p);
        *o = sdscatlen(*o," => ",4);
        p = ldbRedisProtocolToHuman(o,p);
        if (j != mbulklen-1) *o = sdscatlen(*o,",",1);
    }
    *o = sdscatlen(*o,"}",1);
    return p;
}