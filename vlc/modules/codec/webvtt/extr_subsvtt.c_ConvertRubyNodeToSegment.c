#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* psz_text; } ;
typedef  TYPE_2__ webvtt_dom_text_t ;
struct TYPE_11__ {TYPE_1__* p_child; int /*<<< orphan*/  psz_tag; } ;
typedef  TYPE_3__ webvtt_dom_tag_t ;
struct TYPE_12__ {scalar_t__ type; struct TYPE_12__* p_next; } ;
typedef  TYPE_4__ webvtt_dom_node_t ;
typedef  int /*<<< orphan*/  text_segment_t ;
struct TYPE_13__ {struct TYPE_13__* p_next; } ;
typedef  TYPE_5__ text_segment_ruby_t ;
struct TYPE_9__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ NODE_TAG ; 
 scalar_t__ NODE_TEXT ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * text_segment_FromRuby (TYPE_5__*) ; 
 TYPE_5__* text_segment_ruby_New (char const*,char*) ; 

__attribute__((used)) static text_segment_t *ConvertRubyNodeToSegment( const webvtt_dom_node_t *p_node )
{
    text_segment_ruby_t *p_ruby = NULL;
    text_segment_ruby_t **pp_rt_append = &p_ruby;

    const char *psz_base = NULL;

    for( ; p_node ; p_node = p_node->p_next )
    {
        if( p_node->type == NODE_TEXT )
        {
            const webvtt_dom_text_t *p_textnode = (const webvtt_dom_text_t *) p_node;
            psz_base = p_textnode->psz_text;
        }
        else if( p_node->type == NODE_TAG )
        {
            const webvtt_dom_tag_t *p_tag = (const webvtt_dom_tag_t *)p_node;
            if( !strcmp(p_tag->psz_tag, "rt") && p_tag->p_child &&
                p_tag->p_child->type == NODE_TEXT )
            {
                const webvtt_dom_text_t *p_rttext = (const webvtt_dom_text_t *)p_tag->p_child;
                *pp_rt_append = text_segment_ruby_New( psz_base, p_rttext->psz_text );
                if( *pp_rt_append )
                    pp_rt_append = &(*pp_rt_append)->p_next;
            }
            psz_base = NULL;
        }
    }

    return ( p_ruby ) ? text_segment_FromRuby( p_ruby ) : NULL;
}