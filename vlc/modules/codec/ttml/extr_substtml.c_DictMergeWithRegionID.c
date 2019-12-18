#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_dictionary_t ;
struct TYPE_7__ {scalar_t__ p_rootnode; } ;
typedef  TYPE_1__ ttml_context_t ;
struct TYPE_8__ {int /*<<< orphan*/  attr_dict; int /*<<< orphan*/  psz_node_name; TYPE_3__* p_child; } ;
typedef  TYPE_2__ tt_node_t ;
struct TYPE_9__ {scalar_t__ i_type; struct TYPE_9__* p_next; } ;
typedef  TYPE_3__ tt_basenode_t ;

/* Variables and functions */
 int /*<<< orphan*/  DictMergeWithStyleID (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DictionaryMerge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* FindNode (scalar_t__,char*,int,char const*) ; 
 scalar_t__ TT_NODE_TYPE_TEXT ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  tt_node_NameCompare (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlc_dictionary_value_for_key (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void DictMergeWithRegionID( ttml_context_t *p_ctx, const char *psz_id,
                                   vlc_dictionary_t *p_dst )
{
    assert(p_ctx->p_rootnode);
    if( psz_id && p_ctx->p_rootnode )
    {
        const tt_node_t *p_regionnode = FindNode( p_ctx->p_rootnode,
                                                 "region", -1, psz_id );
        if( !p_regionnode )
            return;

        DictionaryMerge( &p_regionnode->attr_dict, p_dst, false );

        const char *psz_styleid = (const char *)
                vlc_dictionary_value_for_key( &p_regionnode->attr_dict, "style" );
        if( psz_styleid )
            DictMergeWithStyleID( p_ctx, psz_styleid, p_dst );

        for( const tt_basenode_t *p_child = p_regionnode->p_child;
                                  p_child; p_child = p_child->p_next )
        {
            if( unlikely( p_child->i_type == TT_NODE_TYPE_TEXT ) )
                continue;

            const tt_node_t *p_node = (const tt_node_t *) p_child;
            if( !tt_node_NameCompare( p_node->psz_node_name, "style" ) )
            {
                DictionaryMerge( &p_node->attr_dict, p_dst, false );
            }
        }
    }
}