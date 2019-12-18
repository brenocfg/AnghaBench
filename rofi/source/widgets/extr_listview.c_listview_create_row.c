#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ multi_select; } ;
typedef  TYPE_1__ listview ;
struct TYPE_20__ {TYPE_1__* textbox; TYPE_1__* box; TYPE_1__* icon; } ;
typedef  TYPE_2__ _listview_row ;
typedef  int TextboxFlags ;
struct TYPE_21__ {scalar_t__ data; } ;
struct TYPE_18__ {scalar_t__ show_icons; } ;
typedef  TYPE_3__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NORMAL ; 
 int /*<<< orphan*/  ROFI_ORIENTATION_HORIZONTAL ; 
 int TB_AUTOHEIGHT ; 
 int TB_INDICATOR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  WIDGET_TYPE_LISTVIEW_ELEMENT ; 
 int /*<<< orphan*/  WIDGET_TYPE_TEXTBOX_TEXT ; 
 int /*<<< orphan*/  box_add (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* box_create (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_14__ config ; 
 int /*<<< orphan*/  g_free ; 
 TYPE_3__* g_list_first (TYPE_3__*) ; 
 int /*<<< orphan*/  g_list_free_full (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* g_list_next (TYPE_3__*) ; 
 TYPE_1__* icon_create (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* rofi_theme_get_list (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 TYPE_1__* textbox_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_set_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void listview_create_row ( listview *lv, _listview_row *row )
{
    TextboxFlags flags = ( lv->multi_select ) ? TB_INDICATOR : 0;
    row->box  = box_create ( WIDGET ( lv ), "element",ROFI_ORIENTATION_HORIZONTAL );
    widget_set_type ( WIDGET(row->box), WIDGET_TYPE_LISTVIEW_ELEMENT);
    GList *list = rofi_theme_get_list ( WIDGET(row->box), "children", "element-icon,element-text");

    row->textbox = NULL;
    row->icon    = NULL;

    for ( GList *iter = g_list_first(list); iter != NULL;iter = g_list_next(iter)){
        if ( strcasecmp((char *)iter->data, "element-icon") == 0 ) {
            if ( config.show_icons ) {
                row->icon = icon_create ( WIDGET ( row->box ), "element-icon" );
                box_add ( row->box, WIDGET ( row->icon ), FALSE);
            }
        } else if ( strcasecmp ((char *)iter->data, "element-text") == 0 ){
            row->textbox= textbox_create ( WIDGET ( row->box ), WIDGET_TYPE_TEXTBOX_TEXT, "element-text", TB_AUTOHEIGHT|flags, NORMAL, "DDD", 0, 0 );
            box_add ( row->box, WIDGET ( row->textbox ), TRUE);
        }
    }
    g_list_free_full ( list, g_free );
}