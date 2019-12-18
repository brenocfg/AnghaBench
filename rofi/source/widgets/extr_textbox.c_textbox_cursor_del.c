#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cursor; int /*<<< orphan*/ * text; } ;
typedef  TYPE_1__ textbox ;

/* Variables and functions */
 int /*<<< orphan*/  textbox_delete (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void textbox_cursor_del ( textbox *tb )
{
    if ( tb == NULL || tb->text == NULL ) {
        return;
    }
    textbox_delete ( tb, tb->cursor, 1 );
}