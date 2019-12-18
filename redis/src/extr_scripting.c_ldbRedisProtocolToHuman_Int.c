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
 char* strchr (char*,char) ; 

char *ldbRedisProtocolToHuman_Int(sds *o, char *reply) {
    char *p = strchr(reply+1,'\r');
    *o = sdscatlen(*o,reply+1,p-reply-1);
    return p+2;
}