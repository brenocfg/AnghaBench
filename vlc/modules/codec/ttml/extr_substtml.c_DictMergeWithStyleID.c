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
typedef  int /*<<< orphan*/  vlc_dictionary_t ;
struct TYPE_5__ {scalar_t__ p_rootnode; } ;
typedef  TYPE_1__ ttml_context_t ;
struct TYPE_6__ {int /*<<< orphan*/  attr_dict; } ;
typedef  TYPE_2__ tt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  DictionaryMerge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* FindNode (scalar_t__,char*,int,char*) ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 char* strtok_r (char*,char*,char**) ; 
 int /*<<< orphan*/  vlc_dictionary_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dictionary_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_dictionary_is_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DictMergeWithStyleID( ttml_context_t *p_ctx, const char *psz_styles,
                                  vlc_dictionary_t *p_dst )
{
    assert(p_ctx->p_rootnode);
    char *psz_dup;
    if( psz_styles && p_ctx->p_rootnode && (psz_dup = strdup( psz_styles )) )
    {
        /* Use temp dict instead of reverse token processing to
         * resolve styles in specified order */
        vlc_dictionary_t tempdict;
        vlc_dictionary_init( &tempdict, 0 );

        char *saveptr;
        char *psz_id = strtok_r( psz_dup, " ", &saveptr );
        while( psz_id )
        {
            /* Lookup referenced style ID */
            const tt_node_t *p_node = FindNode( p_ctx->p_rootnode,
                                                "style", -1, psz_id );
            if( p_node )
                DictionaryMerge( &p_node->attr_dict, &tempdict, true );

            psz_id = strtok_r( NULL, " ", &saveptr );
        }

        if( !vlc_dictionary_is_empty( &tempdict ) )
            DictionaryMerge( &tempdict, p_dst, false );

        vlc_dictionary_clear( &tempdict, NULL, NULL );
        free( psz_dup );
    }
}