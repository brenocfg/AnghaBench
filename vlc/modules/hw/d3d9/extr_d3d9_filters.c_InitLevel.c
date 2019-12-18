#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct filter_level {float default_val; int /*<<< orphan*/  Range; int /*<<< orphan*/  level; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_6__ {int /*<<< orphan*/  f; } ;
struct TYPE_5__ {int /*<<< orphan*/  f; } ;
struct TYPE_7__ {TYPE_2__ max; TYPE_1__ min; } ;
typedef  TYPE_3__ module_config_t ;
typedef  int /*<<< orphan*/  filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  StoreLevel (struct filter_level*,int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* config_FindConfig (char const*) ; 
 float var_CreateGetFloatCommand (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void InitLevel(filter_t *filter, struct filter_level *range, const char *p_name, float def)
{
    module_config_t *cfg = config_FindConfig(p_name);
    range->min = cfg->min.f;
    range->max = cfg->max.f;
    range->default_val = def;

    float val = var_CreateGetFloatCommand( filter, p_name );

    atomic_init( &range->level, StoreLevel( range, &range->Range, val ) );
}