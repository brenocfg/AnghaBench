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
struct TYPE_3__ {char* text; int blink; int /*<<< orphan*/  changed; } ;
typedef  TYPE_1__ textbox ;

/* Variables and functions */
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 char* g_realloc (char*,int) ; 
 char* g_utf8_offset_to_pointer (char*,int const) ; 
 int /*<<< orphan*/  memmove (char*,char const*,int const) ; 
 scalar_t__ strlen (char*) ; 

void textbox_insert ( textbox *tb, const int char_pos, const char *str, const int slen )
{
    if ( tb == NULL ) {
        return;
    }
    char *c  = g_utf8_offset_to_pointer ( tb->text, char_pos );
    int  pos = c - tb->text;
    int  len = ( int ) strlen ( tb->text );
    pos = MAX ( 0, MIN ( len, pos ) );
    // expand buffer
    tb->text = g_realloc ( tb->text, len + slen + 1 );
    // move everything after cursor upward
    char *at = tb->text + pos;
    memmove ( at + slen, at, len - pos + 1 );
    // insert new str
    memmove ( at, str, slen );

    // Set modified, lay out need te be redrawn
    // Stop blink!
    tb->blink   = 2;
    tb->changed = TRUE;
}