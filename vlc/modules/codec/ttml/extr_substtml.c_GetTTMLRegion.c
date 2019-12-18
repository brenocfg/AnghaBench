#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int i_size; TYPE_2__** p_entries; } ;
typedef  TYPE_1__ vlc_dictionary_t ;
struct TYPE_11__ {int /*<<< orphan*/  p_value; int /*<<< orphan*/  psz_key; struct TYPE_11__* p_next; } ;
typedef  TYPE_2__ vlc_dictionary_entry_t ;
typedef  int /*<<< orphan*/  ttml_region_t ;
struct TYPE_12__ {int /*<<< orphan*/  regions; } ;
typedef  TYPE_3__ ttml_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  DictMergeWithRegionID (TYPE_3__*,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  FillRegionStyle (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * ttml_region_New (int) ; 
 int /*<<< orphan*/  vlc_dictionary_clear (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dictionary_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_dictionary_insert (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_dictionary_value_for_key (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static ttml_region_t *GetTTMLRegion( ttml_context_t *p_ctx, const char *psz_region_id )
{
    ttml_region_t *p_region = ( ttml_region_t * )
            vlc_dictionary_value_for_key( &p_ctx->regions, psz_region_id ? psz_region_id : "" );
    if( p_region == NULL )
    {
        if( psz_region_id && strcmp( psz_region_id, "" ) ) /* not default region */
        {
            /* Create region if if missing */

            vlc_dictionary_t merged;
            vlc_dictionary_init( &merged, 0 );
            /* Get all attributes, including region > style */
            DictMergeWithRegionID( p_ctx, psz_region_id, &merged );
            if( (p_region = ttml_region_New( false )) )
            {
                /* Fill from its own attributes */
                for( int i = 0; i < merged.i_size; ++i )
                {
                    for ( vlc_dictionary_entry_t* p_entry = merged.p_entries[i];
                          p_entry != NULL; p_entry = p_entry->p_next )
                    {
                        FillRegionStyle( p_ctx, p_entry->psz_key, p_entry->p_value,
                                         p_region );
                    }
                }
            }
            vlc_dictionary_clear( &merged, NULL, NULL );

            vlc_dictionary_insert( &p_ctx->regions, psz_region_id, p_region );
        }
        else if( (p_region = ttml_region_New( true )) ) /* create default */
        {
            vlc_dictionary_insert( &p_ctx->regions, "", p_region );
        }
    }
    return p_region;
}