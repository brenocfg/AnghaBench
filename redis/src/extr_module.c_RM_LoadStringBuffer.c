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
typedef  int /*<<< orphan*/  RedisModuleIO ;

/* Variables and functions */
 char* moduleLoadString (int /*<<< orphan*/ *,int,size_t*) ; 

char *RM_LoadStringBuffer(RedisModuleIO *io, size_t *lenptr) {
    return moduleLoadString(io,1,lenptr);
}