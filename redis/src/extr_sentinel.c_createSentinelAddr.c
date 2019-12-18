#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int port; int /*<<< orphan*/  ip; } ;
typedef  TYPE_1__ sentinelAddr ;
typedef  int /*<<< orphan*/  ip ;

/* Variables and functions */
 scalar_t__ ANET_ERR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int NET_IP_STR_LEN ; 
 scalar_t__ anetResolve (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_1__* zmalloc (int) ; 

sentinelAddr *createSentinelAddr(char *hostname, int port) {
    char ip[NET_IP_STR_LEN];
    sentinelAddr *sa;

    if (port < 0 || port > 65535) {
        errno = EINVAL;
        return NULL;
    }
    if (anetResolve(NULL,hostname,ip,sizeof(ip)) == ANET_ERR) {
        errno = ENOENT;
        return NULL;
    }
    sa = zmalloc(sizeof(*sa));
    sa->ip = sdsnew(ip);
    sa->port = port;
    return sa;
}