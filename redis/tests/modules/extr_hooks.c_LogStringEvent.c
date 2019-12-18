#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  count; scalar_t__ last_val_string; } ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;
typedef  TYPE_1__ EventElement ;

/* Variables and functions */
 TYPE_1__* RedisModule_Alloc (int) ; 
 scalar_t__ RedisModule_CreateString (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* RedisModule_DictGetC (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_DictSetC (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  RedisModule_FreeString (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  event_log ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void LogStringEvent(RedisModuleCtx *ctx, const char* keyname, const char* data) {
    EventElement *event = RedisModule_DictGetC(event_log, (void*)keyname, strlen(keyname), NULL);
    if (!event) {
        event = RedisModule_Alloc(sizeof(EventElement));
        memset(event, 0, sizeof(EventElement));
        RedisModule_DictSetC(event_log, (void*)keyname, strlen(keyname), event);
    }
    if (event->last_val_string) RedisModule_FreeString(ctx, event->last_val_string);
    event->last_val_string = RedisModule_CreateString(ctx, data, strlen(data));
    event->count++;
}