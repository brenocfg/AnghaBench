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
 int /*<<< orphan*/  ANET_CONNECT_NONE ; 
 int anetUnixGenericConnect (char*,char*,int /*<<< orphan*/ ) ; 

int anetUnixConnect(char *err, char *path)
{
    return anetUnixGenericConnect(err,path,ANET_CONNECT_NONE);
}