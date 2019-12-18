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
 char* ldbRedisProtocolToHuman_Bool (int /*<<< orphan*/ *,char*) ; 
 char* ldbRedisProtocolToHuman_Bulk (int /*<<< orphan*/ *,char*) ; 
 char* ldbRedisProtocolToHuman_Double (int /*<<< orphan*/ *,char*) ; 
 char* ldbRedisProtocolToHuman_Int (int /*<<< orphan*/ *,char*) ; 
 char* ldbRedisProtocolToHuman_Map (int /*<<< orphan*/ *,char*) ; 
 char* ldbRedisProtocolToHuman_MultiBulk (int /*<<< orphan*/ *,char*) ; 
 char* ldbRedisProtocolToHuman_Null (int /*<<< orphan*/ *,char*) ; 
 char* ldbRedisProtocolToHuman_Set (int /*<<< orphan*/ *,char*) ; 
 char* ldbRedisProtocolToHuman_Status (int /*<<< orphan*/ *,char*) ; 

char *ldbRedisProtocolToHuman(sds *o, char *reply) {
    char *p = reply;
    switch(*p) {
    case ':': p = ldbRedisProtocolToHuman_Int(o,reply); break;
    case '$': p = ldbRedisProtocolToHuman_Bulk(o,reply); break;
    case '+': p = ldbRedisProtocolToHuman_Status(o,reply); break;
    case '-': p = ldbRedisProtocolToHuman_Status(o,reply); break;
    case '*': p = ldbRedisProtocolToHuman_MultiBulk(o,reply); break;
    case '~': p = ldbRedisProtocolToHuman_Set(o,reply); break;
    case '%': p = ldbRedisProtocolToHuman_Map(o,reply); break;
    case '_': p = ldbRedisProtocolToHuman_Null(o,reply); break;
    case '#': p = ldbRedisProtocolToHuman_Bool(o,reply); break;
    case ',': p = ldbRedisProtocolToHuman_Double(o,reply); break;
    }
    return p;
}