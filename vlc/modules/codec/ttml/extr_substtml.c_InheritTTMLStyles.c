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
typedef  int /*<<< orphan*/  vlc_dictionary_t ;
typedef  int /*<<< orphan*/  ttml_style_t ;
typedef  int /*<<< orphan*/  ttml_context_t ;
struct TYPE_4__ {int /*<<< orphan*/  attr_dict; struct TYPE_4__* p_parent; } ;
typedef  TYPE_1__ tt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  DictMergeWithRegionID (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DictMergeWithStyleID (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DictToTTMLStyle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DictionaryMerge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/ * ttml_style_New () ; 
 int /*<<< orphan*/  vlc_dictionary_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dictionary_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_dictionary_is_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_dictionary_value_for_key (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ttml_style_t * InheritTTMLStyles( ttml_context_t *p_ctx, tt_node_t *p_node )
{
    assert( p_node );
    ttml_style_t *p_ttml_style = NULL;
    vlc_dictionary_t merged;
    vlc_dictionary_init( &merged, 0 );

    /* Merge dics backwards without overwriting */
    for( ; p_node; p_node = p_node->p_parent )
    {
        DictionaryMerge( &p_node->attr_dict, &merged, false );

        const char *psz_styleid = (const char *)
                vlc_dictionary_value_for_key( &p_node->attr_dict, "style" );
        if( psz_styleid )
            DictMergeWithStyleID( p_ctx, psz_styleid, &merged );

        const char *psz_regionid = (const char *)
                vlc_dictionary_value_for_key( &p_node->attr_dict, "region" );
        if( psz_regionid )
            DictMergeWithRegionID( p_ctx, psz_regionid, &merged );
    }

    if( !vlc_dictionary_is_empty( &merged ) && (p_ttml_style = ttml_style_New()) )
    {
        DictToTTMLStyle( p_ctx, &merged, p_ttml_style );
    }

    vlc_dictionary_clear( &merged, NULL, NULL );

    return p_ttml_style;
}