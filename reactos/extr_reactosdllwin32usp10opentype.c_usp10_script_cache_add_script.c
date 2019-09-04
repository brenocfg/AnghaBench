#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tag; } ;
struct TYPE_5__ {scalar_t__ script_count; TYPE_2__* scripts; int /*<<< orphan*/  scripts_size; } ;
typedef  TYPE_1__ ScriptCache ;
typedef  int /*<<< orphan*/  OPENTYPE_TAG ;
typedef  TYPE_2__ LoadedScript ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  usp10_array_reserve (void**,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static LoadedScript *usp10_script_cache_add_script(ScriptCache *script_cache, OPENTYPE_TAG tag)
{
    LoadedScript *script;

    if (!usp10_array_reserve((void **)&script_cache->scripts, &script_cache->scripts_size,
            script_cache->script_count + 1, sizeof(*script_cache->scripts)))
    {
        ERR("Failed to grow scripts array.\n");
        return NULL;
    }

    script = &script_cache->scripts[script_cache->script_count++];
    script->tag = tag;

    return script;
}