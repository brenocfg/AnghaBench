#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  textbox ;

/* Variables and functions */
 int /*<<< orphan*/  WIDGET (int /*<<< orphan*/  const*) ; 
 int textbox_get_font_height (int /*<<< orphan*/  const*) ; 
 int widget_padding_get_padding_height (int /*<<< orphan*/ ) ; 

int textbox_get_height ( const textbox *tb )
{
    return textbox_get_font_height ( tb ) + widget_padding_get_padding_height ( WIDGET ( tb ) );
}