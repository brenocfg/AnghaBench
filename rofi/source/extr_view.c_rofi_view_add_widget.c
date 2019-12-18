#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  widget ;
typedef  int /*<<< orphan*/  textbox ;
typedef  int /*<<< orphan*/  icon ;
typedef  int /*<<< orphan*/  box ;
typedef  int TextboxFlags ;
struct TYPE_16__ {scalar_t__ data; } ;
struct TYPE_15__ {int menu_flags; int num_modi; int /*<<< orphan*/ * overlay; int /*<<< orphan*/ ** modi; int /*<<< orphan*/ * sidebar_bar; int /*<<< orphan*/  const* sw; int /*<<< orphan*/  num_lines; int /*<<< orphan*/ * list_view; int /*<<< orphan*/ * mesg_box; int /*<<< orphan*/ * mesg_tb; int /*<<< orphan*/ * text; int /*<<< orphan*/ * case_indicator; int /*<<< orphan*/ * tb_filtered_rows; int /*<<< orphan*/ * tb_total_rows; int /*<<< orphan*/ * prompt; } ;
struct TYPE_14__ {int /*<<< orphan*/  menu_lines; int /*<<< orphan*/  scroll_method; int /*<<< orphan*/  element_height; scalar_t__ sidebar_mode; } ;
typedef  TYPE_1__ RofiViewState ;
typedef  int /*<<< orphan*/  Mode ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HIGHLIGHT ; 
 int MENU_INDICATOR ; 
 int MENU_PASSWORD ; 
 int /*<<< orphan*/  NORMAL ; 
 int /*<<< orphan*/  ROFI_ORIENTATION_HORIZONTAL ; 
 int /*<<< orphan*/  ROFI_ORIENTATION_VERTICAL ; 
 int TB_AUTOHEIGHT ; 
 int TB_AUTOWIDTH ; 
 int TB_EDITABLE ; 
 int TB_MARKUP ; 
 int TB_PASSWORD ; 
 int TB_WRAP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  URGENT ; 
 int /*<<< orphan*/ * WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WIDGET_TYPE_EDITBOX ; 
 int /*<<< orphan*/  WIDGET_TYPE_MODE_SWITCHER ; 
 int /*<<< orphan*/  WIDGET_TYPE_TEXTBOX_TEXT ; 
 int /*<<< orphan*/  box_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * box_create (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 TYPE_13__ config ; 
 int /*<<< orphan*/  container_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * container_create (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ g_ascii_strcasecmp (char const*,char*) ; 
 scalar_t__ g_ascii_strncasecmp (char const*,char*,int) ; 
 int /*<<< orphan*/  g_error (char*) ; 
 int /*<<< orphan*/  g_free ; 
 int /*<<< orphan*/  g_list_free_full (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* g_list_next (TYPE_2__ const*) ; 
 int /*<<< orphan*/ ** g_malloc0 (int) ; 
 int /*<<< orphan*/  get_matching_state () ; 
 int /*<<< orphan*/ * icon_create (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * listview_create (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listview_set_max_lines (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listview_set_mouse_activated_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  listview_set_multi_select (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  listview_set_num_lines (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  listview_set_scroll_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* mode_get_display_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * rofi_get_mode (unsigned int) ; 
 int rofi_get_num_enabled_modi () ; 
 int rofi_theme_get_integer (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* rofi_theme_get_list (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  rofi_view_listview_mouse_activated_cb ; 
 int /*<<< orphan*/  rofi_view_reload_message_bar (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_update_prompt (TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  textbox_button_trigger_action ; 
 void* textbox_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,char*,double,double) ; 
 int /*<<< orphan*/  textbox_sidebar_modi_trigger_action ; 
 int /*<<< orphan*/  textbox_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_callback ; 
 int /*<<< orphan*/  widget_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  widget_set_trigger_action_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void rofi_view_add_widget ( RofiViewState *state, widget *parent_widget, const char *name )
{
    char   *defaults = NULL;
    widget *wid      = NULL;

    /**
     * MAINBOX
     */
    if ( strcmp ( name, "mainbox" ) == 0 ) {
        wid = (widget *) box_create ( parent_widget, name, ROFI_ORIENTATION_VERTICAL );
        box_add ( (box *) parent_widget, WIDGET ( wid ), TRUE );
        if ( config.sidebar_mode ) {
            defaults = "inputbar,message,listview,mode-switcher";
        } else {
            defaults = "inputbar,message,listview";
        }
    }
    /**
     * INPUTBAR
     */
    else if ( strcmp ( name, "inputbar" ) == 0 ) {
        wid      = (widget *) box_create ( parent_widget, name, ROFI_ORIENTATION_HORIZONTAL );
        defaults = "prompt,entry,overlay,case-indicator";
        box_add ( (box *) parent_widget, WIDGET ( wid ), FALSE );
    }
    /**
     * PROMPT
     */
    else if ( strcmp ( name, "prompt" ) == 0 ) {
        if ( state->prompt != NULL ) {
            g_error ( "Prompt widget can only be added once to the layout." );
            return;
        }
        // Prompt box.
        state->prompt = textbox_create ( parent_widget, WIDGET_TYPE_TEXTBOX_TEXT, name, TB_AUTOWIDTH | TB_AUTOHEIGHT, NORMAL, "", 0, 0 );
        rofi_view_update_prompt ( state );
        box_add ( (box *) parent_widget, WIDGET ( state->prompt ), FALSE );
        defaults = NULL;
    }
    else if ( strcmp ( name, "num-rows" ) == 0 ){
        state->tb_total_rows = textbox_create ( parent_widget, WIDGET_TYPE_TEXTBOX_TEXT, name, TB_AUTOWIDTH|TB_AUTOHEIGHT, NORMAL, "", 0, 0 );
        box_add ( (box *) parent_widget, WIDGET ( state->tb_total_rows ), FALSE );
        defaults = NULL;
    }
    else if ( strcmp ( name, "num-filtered-rows" ) == 0 ){
        state->tb_filtered_rows = textbox_create ( parent_widget, WIDGET_TYPE_TEXTBOX_TEXT, name, TB_AUTOWIDTH|TB_AUTOHEIGHT, NORMAL, "", 0, 0 );
        box_add ( (box *) parent_widget, WIDGET ( state->tb_filtered_rows), FALSE );
        defaults = NULL;
    }
    /**
     * CASE INDICATOR
     */
    else if ( strcmp ( name, "case-indicator" ) == 0 ) {
        if ( state->case_indicator != NULL ) {
            g_error ( "Case indicator widget can only be added once to the layout." );
            return;
        }
        state->case_indicator = textbox_create ( parent_widget, WIDGET_TYPE_TEXTBOX_TEXT, name, TB_AUTOWIDTH | TB_AUTOHEIGHT, NORMAL, "*", 0, 0 );
        // Add small separator between case indicator and text box.
        box_add ( (box *) parent_widget, WIDGET ( state->case_indicator ), FALSE );
        textbox_text ( state->case_indicator, get_matching_state () );
    }
    /**
     * ENTRY BOX
     */
    else if ( strcmp ( name, "entry" ) == 0 ) {
        if ( state->text != NULL ) {
            g_error ( "Entry textbox widget can only be added once to the layout." );
            return;
        }
        // Entry box
        TextboxFlags tfl = TB_EDITABLE;
        tfl        |= ( ( state->menu_flags & MENU_PASSWORD ) == MENU_PASSWORD ) ? TB_PASSWORD : 0;
        state->text = textbox_create ( parent_widget, WIDGET_TYPE_EDITBOX, name, tfl | TB_AUTOHEIGHT, NORMAL, NULL, 0, 0 );
        box_add ( (box *) parent_widget, WIDGET ( state->text ), TRUE );
    }
    /**
     * MESSAGE
     */
    else if ( strcmp ( name, "message" ) == 0 ) {
        if ( state->mesg_box != NULL ) {
            g_error ( "Message widget can only be added once to the layout." );
            return;
        }
        state->mesg_box = container_create ( parent_widget, name );
        state->mesg_tb  = textbox_create ( WIDGET ( state->mesg_box ), WIDGET_TYPE_TEXTBOX_TEXT, "textbox", TB_AUTOHEIGHT | TB_MARKUP | TB_WRAP, NORMAL, NULL, 0, 0 );
        container_add ( state->mesg_box, WIDGET ( state->mesg_tb ) );
        rofi_view_reload_message_bar ( state );
        box_add ( (box *) parent_widget, WIDGET ( state->mesg_box ), FALSE );
    }
    /**
     * LISTVIEW
     */
    else if ( strcmp ( name, "listview" ) == 0 ) {
        if ( state->list_view != NULL ) {
            g_error ( "Listview widget can only be added once to the layout." );
            return;
        }
        state->list_view = listview_create ( parent_widget, name, update_callback, state, config.element_height, 0 );
        box_add ( (box *) parent_widget, WIDGET ( state->list_view ), TRUE );
        // Set configuration
        listview_set_multi_select ( state->list_view, ( state->menu_flags & MENU_INDICATOR ) == MENU_INDICATOR );
        listview_set_scroll_type ( state->list_view, config.scroll_method );
        listview_set_mouse_activated_cb ( state->list_view, rofi_view_listview_mouse_activated_cb, state );

        int lines = rofi_theme_get_integer ( WIDGET ( state->list_view ), "lines", config.menu_lines );
        listview_set_num_lines ( state->list_view, lines );
        listview_set_max_lines ( state->list_view, state->num_lines );
    }
    /**
     * MODE SWITCHER
     */
    else if ( strcmp ( name, "mode-switcher" ) == 0 || strcmp ( name, "sidebar" ) == 0 ) {
        if ( state->sidebar_bar != NULL ) {
            g_error ( "Mode-switcher can only be added once to the layout." );
            return;
        }
        state->sidebar_bar = box_create ( parent_widget, name, ROFI_ORIENTATION_HORIZONTAL );
        box_add ( (box *) parent_widget, WIDGET ( state->sidebar_bar ), FALSE );
        state->num_modi = rofi_get_num_enabled_modi ();
        state->modi     = g_malloc0 ( state->num_modi * sizeof ( textbox * ) );
        for ( unsigned int j = 0; j < state->num_modi; j++ ) {
            const Mode * mode = rofi_get_mode ( j );
            state->modi[j] = textbox_create ( WIDGET ( state->sidebar_bar ), WIDGET_TYPE_MODE_SWITCHER, "button", TB_AUTOHEIGHT, ( mode == state->sw ) ? HIGHLIGHT : NORMAL,
                    mode_get_display_name ( mode  ), 0.5, 0.5 );
            box_add ( state->sidebar_bar, WIDGET ( state->modi[j] ), TRUE );
            widget_set_trigger_action_handler ( WIDGET ( state->modi[j] ), textbox_sidebar_modi_trigger_action, state );
        }
    }
    else if ( g_ascii_strcasecmp ( name, "overlay" ) == 0 ) {
        state->overlay = textbox_create ( WIDGET ( parent_widget ), WIDGET_TYPE_TEXTBOX_TEXT, "overlay", TB_AUTOWIDTH | TB_AUTOHEIGHT, URGENT, "blaat", 0.5, 0 );
        box_add ( (box *) parent_widget, WIDGET ( state->overlay), FALSE );
        widget_disable ( WIDGET ( state->overlay ) );
    }
    else if (  g_ascii_strncasecmp ( name, "textbox", 7 ) == 0 ) {
        textbox *t = textbox_create ( parent_widget, WIDGET_TYPE_TEXTBOX_TEXT, name, TB_AUTOHEIGHT | TB_WRAP, NORMAL, "", 0, 0 );
        box_add ( (box *) parent_widget, WIDGET ( t ), TRUE );
    }
    else if (  g_ascii_strncasecmp ( name, "button", 6 ) == 0 ) {
        textbox *t = textbox_create ( parent_widget, WIDGET_TYPE_EDITBOX, name, TB_AUTOHEIGHT | TB_WRAP, NORMAL, "", 0, 0 );
        box_add ( (box *) parent_widget, WIDGET ( t ), TRUE );
        widget_set_trigger_action_handler ( WIDGET ( t ), textbox_button_trigger_action, state );
    }
    else if (  g_ascii_strncasecmp ( name, "icon", 4 ) == 0 ) {
        icon *t = icon_create ( parent_widget, name );
        box_add ( (box *) parent_widget, WIDGET ( t ), TRUE );
    }
    else {
        wid = (widget *) box_create ( parent_widget, name, ROFI_ORIENTATION_VERTICAL );
        box_add ( (box *) parent_widget, WIDGET ( wid ), TRUE );
        //g_error("The widget %s does not exists. Invalid layout.", name);
    }
    if ( wid ) {
        GList *list = rofi_theme_get_list ( wid, "children", defaults );
        for ( const GList *iter = list; iter != NULL; iter = g_list_next ( iter ) ) {
            rofi_view_add_widget ( state, wid, (const char *) iter->data );
        }
        g_list_free_full ( list, g_free );
    }
}