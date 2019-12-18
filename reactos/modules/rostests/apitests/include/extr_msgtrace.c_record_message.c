#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int iwnd; scalar_t__ msg; int param1; int param2; scalar_t__ type; } ;
struct TYPE_4__ {int count; TYPE_3__ last_post_message; TYPE_3__* message_cache; } ;
typedef  scalar_t__ MSG_TYPE ;
typedef  int /*<<< orphan*/  MSG_ENTRY ;
typedef  TYPE_1__ MSG_CACHE ;

/* Variables and functions */
 scalar_t__ POST ; 
 scalar_t__ SENT ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void record_message(MSG_CACHE* cache, int iwnd, UINT message, MSG_TYPE type, int param1,int param2)
{
    if(cache->count >= 100)
    {
        return;
    }

    /* do not report a post message a second time */
    if(type == SENT &&
       cache->last_post_message.iwnd == iwnd && 
       cache->last_post_message.msg == message && 
       cache->last_post_message.param1 == param1 && 
       cache->last_post_message.param2 == param2)
    {
        memset(&cache->last_post_message, 0, sizeof(MSG_ENTRY));
        return;
    }

    cache->message_cache[cache->count].iwnd = iwnd;
    cache->message_cache[cache->count].msg = message;
    cache->message_cache[cache->count].type = type;
    cache->message_cache[cache->count].param1 = param1;
    cache->message_cache[cache->count].param2 = param2;

    if(cache->message_cache[cache->count].type == POST)
    {
        cache->last_post_message = cache->message_cache[cache->count];
    }
    else
    {
        memset(&cache->last_post_message, 0, sizeof(MSG_ENTRY));
    }

    cache->count++;
}