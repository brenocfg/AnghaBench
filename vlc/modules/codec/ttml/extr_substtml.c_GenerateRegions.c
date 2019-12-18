#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ p_value; struct TYPE_17__* p_next; } ;
typedef  TYPE_2__ vlc_dictionary_entry_t ;
struct TYPE_16__ {int /*<<< orphan*/  p_next; } ;
struct TYPE_18__ {TYPE_1__ updt; } ;
typedef  TYPE_3__ ttml_region_t ;
struct TYPE_21__ {int i_size; TYPE_2__** p_entries; } ;
struct TYPE_19__ {TYPE_6__ regions; TYPE_5__* p_rootnode; } ;
typedef  TYPE_4__ ttml_context_t ;
typedef  int /*<<< orphan*/  tt_time_t ;
struct TYPE_20__ {int /*<<< orphan*/  psz_node_name; } ;
typedef  TYPE_5__ tt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertNodesToRegionContent (TYPE_4__*,TYPE_5__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* FindNode (TYPE_5__*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitTTMLContext (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  tt_node_NameCompare (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_dictionary_clear (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dictionary_init (TYPE_6__*,int) ; 

__attribute__((used)) static ttml_region_t *GenerateRegions( tt_node_t *p_rootnode, tt_time_t playbacktime )
{
    ttml_region_t*  p_regions = NULL;
    ttml_region_t** pp_region_last = &p_regions;

    if( !tt_node_NameCompare( p_rootnode->psz_node_name, "tt" ) )
    {
        const tt_node_t *p_bodynode = FindNode( p_rootnode, "body", 1, NULL );
        if( p_bodynode )
        {
            ttml_context_t context;
            InitTTMLContext( p_rootnode, &context );
            context.p_rootnode = p_rootnode;

            vlc_dictionary_init( &context.regions, 1 );
            ConvertNodesToRegionContent( &context, p_bodynode, NULL, NULL, playbacktime );

            for( int i = 0; i < context.regions.i_size; ++i )
            {
                for ( const vlc_dictionary_entry_t* p_entry = context.regions.p_entries[i];
                                                    p_entry != NULL; p_entry = p_entry->p_next )
                {
                    *pp_region_last = (ttml_region_t *) p_entry->p_value;
                    pp_region_last = (ttml_region_t **) &(*pp_region_last)->updt.p_next;
                }
            }

            vlc_dictionary_clear( &context.regions, NULL, NULL );
        }
    }
    else if ( !tt_node_NameCompare( p_rootnode->psz_node_name, "div" ) ||
              !tt_node_NameCompare( p_rootnode->psz_node_name, "p" ) )
    {
        /* TODO */
    }

    return p_regions;
}