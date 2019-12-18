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
 int /*<<< orphan*/  sdscatrepr (int /*<<< orphan*/ ,char*,int) ; 
 char* strchr (char*,char) ; 

char *ldbRedisProtocolToHuman_Status(sds *o, char *reply) {
    char *p = strchr(reply+1,'\r');

    *o = sdscatrepr(*o,reply,p-reply);
    return p+2;
}