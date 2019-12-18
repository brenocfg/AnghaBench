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
struct TYPE_3__ {int flags; char* text; int tbft; int /*<<< orphan*/  layout; } ;
typedef  TYPE_1__ textbox ;

/* Variables and functions */
 int MARKUP ; 
 int TB_MARKUP ; 
 int TB_PASSWORD ; 
 size_t g_utf8_strlen (char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 int /*<<< orphan*/  pango_layout_set_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_layout_set_markup (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pango_layout_set_text (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void __textbox_update_pango_text ( textbox *tb )
{
    pango_layout_set_attributes ( tb->layout, NULL );
    if ( ( tb->flags & TB_PASSWORD ) == TB_PASSWORD ) {
        size_t l = g_utf8_strlen ( tb->text, -1 );
        char   string [l + 1];
        memset ( string, '*', l );
        string[l] = '\0';
        pango_layout_set_text ( tb->layout, string, l );
    }
    else if ( tb->flags & TB_MARKUP || tb->tbft & MARKUP ) {
        pango_layout_set_markup ( tb->layout, tb->text, -1 );
    }
    else {
        pango_layout_set_text ( tb->layout, tb->text, -1 );
    }
}