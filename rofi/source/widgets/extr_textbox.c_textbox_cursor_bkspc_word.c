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
struct TYPE_5__ {scalar_t__ cursor; } ;
typedef  TYPE_1__ textbox ;

/* Variables and functions */
 int /*<<< orphan*/  textbox_cursor_dec_word (TYPE_1__*) ; 
 int /*<<< orphan*/  textbox_delete (TYPE_1__*,int,int) ; 

__attribute__((used)) static void textbox_cursor_bkspc_word ( textbox *tb )
{
    if ( tb && tb->cursor > 0 ) {
        int cursor = tb->cursor;
        textbox_cursor_dec_word ( tb );
        if ( cursor > tb->cursor ) {
            textbox_delete ( tb, tb->cursor, cursor - tb->cursor );
        }
    }
}