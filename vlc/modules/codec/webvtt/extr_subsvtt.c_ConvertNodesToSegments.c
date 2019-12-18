#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * psz_text; } ;
typedef  TYPE_1__ webvtt_dom_text_t ;
struct TYPE_12__ {TYPE_3__* p_child; int /*<<< orphan*/  psz_tag; } ;
typedef  TYPE_2__ webvtt_dom_tag_t ;
struct TYPE_13__ {scalar_t__ type; struct TYPE_13__* p_next; } ;
typedef  TYPE_3__ webvtt_dom_node_t ;
typedef  int /*<<< orphan*/  webvtt_dom_cue_t ;
struct TYPE_14__ {int /*<<< orphan*/  style; scalar_t__ psz_text; struct TYPE_14__* p_next; } ;
typedef  TYPE_4__ text_segment_t ;
struct render_variables_s {int dummy; } ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  ComputeStyle (int /*<<< orphan*/ *,TYPE_3__ const*) ; 
 TYPE_4__* ConvertRubyNodeToSegment (TYPE_3__*) ; 
 scalar_t__ NODE_TAG ; 
 scalar_t__ NODE_TEXT ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* text_segment_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_xml_decode (scalar_t__) ; 

__attribute__((used)) static text_segment_t *ConvertNodesToSegments( decoder_t *p_dec,
                                               struct render_variables_s *p_vars,
                                               const webvtt_dom_cue_t *p_cue,
                                               const webvtt_dom_node_t *p_node )
{
    text_segment_t *p_head = NULL;
    text_segment_t **pp_append = &p_head;
    for( ; p_node ; p_node = p_node->p_next )
    {
        while( *pp_append )
            pp_append = &((*pp_append)->p_next);

        if( p_node->type == NODE_TEXT )
        {
            const webvtt_dom_text_t *p_textnode = (const webvtt_dom_text_t *) p_node;
            if( p_textnode->psz_text == NULL )
                continue;

            *pp_append = text_segment_New( p_textnode->psz_text );
            if( *pp_append )
            {
                if( (*pp_append)->psz_text )
                    vlc_xml_decode( (*pp_append)->psz_text );
                (*pp_append)->style = ComputeStyle( p_dec, p_node );
            }
        }
        else if( p_node->type == NODE_TAG )
        {
            const webvtt_dom_tag_t *p_tag = (const webvtt_dom_tag_t *)p_node;
            if( strcmp(p_tag->psz_tag, "ruby") )
                *pp_append = ConvertNodesToSegments( p_dec, p_vars, p_cue,
                                                     p_tag->p_child );
            else
                *pp_append = ConvertRubyNodeToSegment( p_tag->p_child );
        }
    }
    return p_head;
}