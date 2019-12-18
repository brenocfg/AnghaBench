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

/* Variables and functions */
 int /*<<< orphan*/  ANET_IP_ONLY ; 
 int anetGenericResolve (char*,char*,char*,size_t,int /*<<< orphan*/ ) ; 

int anetResolveIP(char *err, char *host, char *ipbuf, size_t ipbuf_len) {
    return anetGenericResolve(err,host,ipbuf,ipbuf_len,ANET_IP_ONLY);
}