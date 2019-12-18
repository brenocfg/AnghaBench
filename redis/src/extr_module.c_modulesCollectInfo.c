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
struct RedisModule {int /*<<< orphan*/  (* info_cb ) (TYPE_1__*,int) ;} ;
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_4__ {int member_3; int sections; int /*<<< orphan*/  info; scalar_t__ in_dict_field; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; struct RedisModule* member_0; } ;
typedef  TYPE_1__ RedisModuleInfoCtx ;

/* Variables and functions */
 int /*<<< orphan*/  RM_InfoEndDictField (TYPE_1__*) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 struct RedisModule* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modules ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

sds modulesCollectInfo(sds info, sds section, int for_crash_report, int sections) {
    dictIterator *di = dictGetIterator(modules);
    dictEntry *de;

    while ((de = dictNext(di)) != NULL) {
        struct RedisModule *module = dictGetVal(de);
        if (!module->info_cb)
            continue;
        RedisModuleInfoCtx info_ctx = {module, section, info, sections, 0};
        module->info_cb(&info_ctx, for_crash_report);
        /* Implicitly end dicts (no way to handle errors, and we must add the newline). */
        if (info_ctx.in_dict_field)
            RM_InfoEndDictField(&info_ctx);
        info = info_ctx.info;
        sections = info_ctx.sections;
    }
    dictReleaseIterator(di);
    return info;
}