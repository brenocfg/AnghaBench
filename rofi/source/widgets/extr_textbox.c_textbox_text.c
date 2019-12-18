#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  cursor; void* text; TYPE_1__ widget; } ;
typedef  TYPE_2__ textbox ;
typedef  char gchar ;
struct TYPE_11__ {scalar_t__ parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
 int TB_AUTOWIDTH ; 
 TYPE_3__* WIDGET (TYPE_2__*) ; 
 int /*<<< orphan*/  __textbox_update_pango_text (TYPE_2__*) ; 
 int /*<<< orphan*/  g_free (void*) ; 
 void* g_strdup (char const*) ; 
 void* g_strndup (char const*,int) ; 
 scalar_t__ g_utf8_strlen (void*,int) ; 
 scalar_t__ g_utf8_validate (char const*,int,char const**) ; 
 int /*<<< orphan*/  textbox_moveresize (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_queue_redraw (TYPE_3__*) ; 
 int /*<<< orphan*/  widget_update (scalar_t__) ; 

void textbox_text ( textbox *tb, const char *text )
{
    if ( tb == NULL ) {
        return;
    }
    g_free ( tb->text );
    const gchar *last_pointer = NULL;

    if ( g_utf8_validate ( text, -1, &last_pointer ) ) {
        tb->text = g_strdup ( text );
    }
    else {
        if ( last_pointer != NULL ) {
            // Copy string up to invalid character.
            tb->text = g_strndup ( text, ( last_pointer - text ) );
        }
        else {
            tb->text = g_strdup ( "Invalid UTF-8 string." );
        }
    }
    __textbox_update_pango_text ( tb );
    if ( tb->flags & TB_AUTOWIDTH ) {
        textbox_moveresize ( tb, tb->widget.x, tb->widget.y, tb->widget.w, tb->widget.h );
        if ( WIDGET ( tb )->parent ) {
            widget_update ( WIDGET ( tb )->parent );
        }
    }

    tb->cursor = MAX ( 0, MIN ( ( int ) g_utf8_strlen ( tb->text, -1 ), tb->cursor ) );
    widget_queue_redraw ( WIDGET ( tb ) );
}