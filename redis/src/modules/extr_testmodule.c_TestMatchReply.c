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
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleCallReply ;

/* Variables and functions */
 int /*<<< orphan*/ * RedisModule_CreateStringFromCallReply (int /*<<< orphan*/ *) ; 
 char* RedisModule_StringPtrLen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int TestMatchReply(RedisModuleCallReply *reply, char *str) {
    RedisModuleString *mystr;
    mystr = RedisModule_CreateStringFromCallReply(reply);
    if (!mystr) return 0;
    const char *ptr = RedisModule_StringPtrLen(mystr,NULL);
    return strcmp(ptr,str) == 0;
}