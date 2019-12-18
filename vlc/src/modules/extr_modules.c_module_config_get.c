#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t size; TYPE_4__* items; } ;
struct TYPE_11__ {TYPE_1__ conf; TYPE_3__ const* module; } ;
typedef  TYPE_2__ vlc_plugin_t ;
struct TYPE_12__ {TYPE_2__* plugin; } ;
typedef  TYPE_3__ module_t ;
struct TYPE_13__ {scalar_t__ b_removed; scalar_t__ b_internal; } ;
typedef  TYPE_4__ module_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__ const*,int) ; 
 TYPE_4__* vlc_alloc (size_t,int) ; 

module_config_t *module_config_get( const module_t *module, unsigned *restrict psize )
{
    const vlc_plugin_t *plugin = module->plugin;

    if (plugin->module != module)
    {   /* For backward compatibility, pretend non-first modules have no
         * configuration items. */
        *psize = 0;
        return NULL;
    }

    unsigned i,j;
    size_t size = plugin->conf.size;
    module_config_t *config = vlc_alloc( size, sizeof( *config ) );

    assert( psize != NULL );
    *psize = 0;

    if( !config )
        return NULL;

    for( i = 0, j = 0; i < size; i++ )
    {
        const module_config_t *item = plugin->conf.items + i;
        if( item->b_internal /* internal option */
         || item->b_removed /* removed option */ )
            continue;

        memcpy( config + j, item, sizeof( *config ) );
        j++;
    }
    *psize = j;

    return config;
}