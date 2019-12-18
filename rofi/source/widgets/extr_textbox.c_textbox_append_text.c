#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; scalar_t__ cursor; } ;
typedef  TYPE_1__ textbox ;
typedef  char gchar ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int TB_EDITABLE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ g_unichar_iscntrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_utf8_get_char (char const*) ; 
 char* g_utf8_next_char (char const*) ; 
 int /*<<< orphan*/  textbox_cursor (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  textbox_insert (TYPE_1__*,scalar_t__,char const*,int) ; 

gboolean textbox_append_text ( textbox *tb, const char *pad, const int pad_len )
{
    if ( tb == NULL ) {
        return FALSE;
    }
    if ( !( tb->flags & TB_EDITABLE ) ) {
        return FALSE;
    }

    // Filter When alt/ctrl is pressed do not accept the character.

    gboolean    used_something = FALSE;
    const gchar *w, *n, *e;
    for ( w = pad, n = g_utf8_next_char ( w ), e = w + pad_len; w < e; w = n, n = g_utf8_next_char ( n ) ) {
        if ( g_unichar_iscntrl ( g_utf8_get_char ( w ) ) ) {
            continue;
        }
        textbox_insert ( tb, tb->cursor, w, n - w );
        textbox_cursor ( tb, tb->cursor + 1 );
        used_something = TRUE;
    }
    return used_something;
}