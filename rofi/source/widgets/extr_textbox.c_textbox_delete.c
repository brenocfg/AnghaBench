#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* text; int cursor; int blink; int /*<<< orphan*/  changed; } ;
typedef  TYPE_1__ textbox ;

/* Variables and functions */
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 char* g_utf8_offset_to_pointer (char*,int) ; 
 int g_utf8_strlen (char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int strlen (char*) ; 

void textbox_delete ( textbox *tb, int pos, int dlen )
{
    if ( tb == NULL ) {
        return;
    }
    int len = g_utf8_strlen ( tb->text, -1 );
    if ( len == pos ) {
        return;
    }
    pos = MAX ( 0, MIN ( len, pos ) );
    if ( ( pos + dlen ) > len ) {
        dlen = len - dlen;
    }
    // move everything after pos+dlen down
    char *start = g_utf8_offset_to_pointer ( tb->text, pos );
    char *end   = g_utf8_offset_to_pointer  ( tb->text, pos + dlen );
    // Move remainder + closing \0
    memmove ( start, end, ( tb->text + strlen ( tb->text ) ) - end + 1 );
    if ( tb->cursor >= pos && tb->cursor < ( pos + dlen ) ) {
        tb->cursor = pos;
    }
    else if ( tb->cursor >= ( pos + dlen ) ) {
        tb->cursor -= dlen;
    }
    // Set modified, lay out need te be redrawn
    // Stop blink!
    tb->blink   = 2;
    tb->changed = TRUE;
}