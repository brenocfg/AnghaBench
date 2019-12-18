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
typedef  int /*<<< orphan*/  widget ;
typedef  int TextBoxFontType ;

/* Variables and functions */
 int ACTIVE ; 
#define  ALT 129 
 int FMOD_MASK ; 
#define  HIGHLIGHT 128 
 int STATE_MASK ; 
 int URGENT ; 
 int /*<<< orphan*/ ** listview_theme_prop_names ; 
 int /*<<< orphan*/  widget_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void listview_set_style ( widget *w, TextBoxFontType tbft )
{
    TextBoxFontType t = tbft & STATE_MASK;
    if ( w == NULL ) {
        return;
    }
    // ACTIVE has priority over URGENT if both set.
    if ( t == ( URGENT | ACTIVE ) ) {
        t = ACTIVE;
    }
    switch ( ( tbft & FMOD_MASK ) )
    {
    case HIGHLIGHT:
        widget_set_state ( w, listview_theme_prop_names[t][1] );
        break;
    case ALT:
        widget_set_state ( w, listview_theme_prop_names[t][2] );
        break;
    default:
        widget_set_state ( w, listview_theme_prop_names[t][0] );
        break;
    }
}