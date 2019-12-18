#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* psz_text; TYPE_3__* p_next; } ;
typedef  TYPE_1__ webvtt_dom_text_t ;
struct TYPE_12__ {TYPE_3__* p_child; int /*<<< orphan*/  i_start; int /*<<< orphan*/ * psz_attrs; void* psz_tag; } ;
typedef  TYPE_2__ webvtt_dom_tag_t ;
struct TYPE_13__ {struct TYPE_13__* p_next; struct TYPE_13__* p_parent; } ;
typedef  TYPE_3__ webvtt_dom_node_t ;

/* Variables and functions */
 unsigned int CountNewLines (void*) ; 
 char* FindNextTag (char const*,char const**) ; 
 int /*<<< orphan*/  IsEndTag (char const*) ; 
 char* SplitTag (char const*,size_t*,char const**) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 void* strdup (char const*) ; 
 void* strndup (char const*,size_t) ; 
 TYPE_2__* webvtt_dom_tag_New (TYPE_3__*) ; 
 TYPE_1__* webvtt_dom_text_New (TYPE_3__*) ; 
 TYPE_3__* webvtt_domnode_getParentByTag (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  webvtt_scan_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static webvtt_dom_node_t * CreateDomNodes( const char *psz_text, unsigned *pi_lines )
{
    webvtt_dom_node_t *p_head = NULL;
    webvtt_dom_node_t **pp_append = &p_head;
    webvtt_dom_node_t *p_parent = p_head;
    *pi_lines = 0;

    while( *psz_text )
    {
        const char *psz_taglast;
        const char *psz_tag = FindNextTag( psz_text, &psz_taglast );
        if( psz_tag )
        {
            if( psz_tag - psz_text > 0 )
            {
                webvtt_dom_text_t *p_node = webvtt_dom_text_New( p_parent );
                if( p_node )
                {
                    p_node->psz_text = strndup( psz_text, psz_tag - psz_text );
                    *pi_lines += ((*pi_lines == 0) ? 1 : 0) + CountNewLines( p_node->psz_text );
                    *pp_append = (webvtt_dom_node_t *) p_node;
                    pp_append = &p_node->p_next;
                }
            }

            if( ! IsEndTag( psz_tag ) )
            {
                webvtt_dom_tag_t *p_node = webvtt_dom_tag_New( p_parent );
                if( p_node )
                {
                    const char *psz_attrs = NULL;
                    size_t i_name;
                    const char *psz_name = SplitTag( psz_tag, &i_name, &psz_attrs );
                    p_node->psz_tag = strndup( psz_name, i_name );
                    if( psz_attrs != psz_taglast )
                        p_node->psz_attrs = strndup( psz_attrs, psz_taglast - psz_attrs );
                    /* <hh:mm::ss:fff> time tags */
                    if( p_node->psz_attrs && isdigit(p_node->psz_attrs[0]) )
                        (void) webvtt_scan_time( p_node->psz_attrs, &p_node->i_start );
                    *pp_append = (webvtt_dom_node_t *) p_node;
                    p_parent = (webvtt_dom_node_t *) p_node;
                    pp_append = &p_node->p_child;
                }
            }
            else
            {
                if( p_parent )
                {
                    const char *psz_attrs = NULL;
                    size_t i_name;
                    const char *psz_name = SplitTag( psz_tag, &i_name, &psz_attrs );
                    char *psz_tagname = strndup( psz_name, i_name );

                    /* Close at matched parent node level due to unclosed tags
                     * like <b><v stuff>foo</b> */
                    p_parent = webvtt_domnode_getParentByTag( p_parent, psz_tagname );
                    if( p_parent ) /* continue as parent next */
                    {
                        pp_append = &p_parent->p_next;
                        p_parent = p_parent->p_parent;
                    }
                    else /* back as top node */
                        pp_append = &p_head->p_next;
                    while( *pp_append )
                        pp_append = &((*pp_append)->p_next);

                    free( psz_tagname );
                }
                else break; /* End tag for non open tag */
            }
            psz_text = psz_taglast + 1;
        }
        else /* Special case: end */
        {
            webvtt_dom_text_t *p_node = webvtt_dom_text_New( p_parent );
            if( p_node )
            {
                p_node->psz_text = strdup( psz_text );
                *pi_lines += ((*pi_lines == 0) ? 1 : 0) + CountNewLines( p_node->psz_text );
                *pp_append = (webvtt_dom_node_t *) p_node;
            }
            break;
        }
    }

    return p_head;
}