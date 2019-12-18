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
struct TYPE_5__ {char const* psz_text; } ;
typedef  TYPE_1__ webvtt_dom_text_t ;
struct TYPE_6__ {scalar_t__ type; struct TYPE_6__* p_next; } ;
typedef  TYPE_2__ webvtt_dom_node_t ;
struct TYPE_7__ {int i_lines; TYPE_2__* p_child; } ;
typedef  TYPE_3__ webvtt_dom_cue_t ;

/* Variables and functions */
 scalar_t__ NODE_TEXT ; 
 int /*<<< orphan*/  free (char const*) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 char* strndup (char const*,size_t) ; 

__attribute__((used)) static unsigned webvtt_dom_cue_Reduced( webvtt_dom_cue_t *p_cue )
{
    if( p_cue->i_lines < 1 )
        return 0;

    for( webvtt_dom_node_t *p_node = p_cue->p_child;
                           p_node; p_node = p_node->p_next )
    {
        if( p_node->type != NODE_TEXT )
            continue;
        webvtt_dom_text_t *p_textnode = (webvtt_dom_text_t *) p_node;
        const char *nl = strchr( p_textnode->psz_text, '\n' );
        if( nl )
        {
            size_t i_len = strlen( p_textnode->psz_text );
            size_t i_remain = i_len - (nl - p_textnode->psz_text);
            char *psz_new = strndup( nl + 1, i_remain );
            free( p_textnode->psz_text );
            p_textnode->psz_text = psz_new;
            return --p_cue->i_lines;
        }
        else
        {
            free( p_textnode->psz_text );
            p_textnode->psz_text = NULL;
            /* FIXME: probably can do a local nodes cleanup */
        }
    }

    return p_cue->i_lines;
}