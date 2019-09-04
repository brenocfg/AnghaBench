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
struct TYPE_4__ {scalar_t__ languages_initialized; int /*<<< orphan*/ ** table; } ;
typedef  int /*<<< orphan*/  OT_Script ;
typedef  TYPE_1__ LoadedScript ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  USP10_LANGUAGE_TABLE_GPOS ; 
 int /*<<< orphan*/  USP10_LANGUAGE_TABLE_GSUB ; 
 size_t USP10_SCRIPT_TABLE_GPOS ; 
 size_t USP10_SCRIPT_TABLE_GSUB ; 
 int /*<<< orphan*/  usp10_script_add_language_list (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void _initialize_language_cache(LoadedScript *script)
{
    const OT_Script *list;

    if (script->languages_initialized)
        return;

    if ((list = script->table[USP10_SCRIPT_TABLE_GSUB]))
        usp10_script_add_language_list(script, USP10_LANGUAGE_TABLE_GSUB, list);
    if ((list = script->table[USP10_SCRIPT_TABLE_GPOS]))
        usp10_script_add_language_list(script, USP10_LANGUAGE_TABLE_GPOS, list);

    script->languages_initialized = TRUE;
}