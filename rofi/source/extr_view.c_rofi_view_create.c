#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_18__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/ * sncontext; int /*<<< orphan*/  connection; } ;
struct TYPE_21__ {scalar_t__ data; } ;
struct TYPE_20__ {int* distance; void (* finalize ) (TYPE_1__*) ;int /*<<< orphan*/  main_window; void* quit; int /*<<< orphan*/  height; int /*<<< orphan*/  list_view; int /*<<< orphan*/  width; int /*<<< orphan*/  num_lines; scalar_t__ line_map; scalar_t__ text; int /*<<< orphan*/ * sw; void* mouse_seen; int /*<<< orphan*/  refilter; void* skip_absorb; int /*<<< orphan*/  retv; int /*<<< orphan*/  selected_line; int /*<<< orphan*/  menu_flags; } ;
struct TYPE_19__ {int flags; int /*<<< orphan*/  main_window; } ;
typedef  TYPE_1__ RofiViewState ;
typedef  int /*<<< orphan*/  Mode ;
typedef  int /*<<< orphan*/  MenuFlags ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 TYPE_18__ CacheState ; 
 void* FALSE ; 
 int /*<<< orphan*/  MENU_CANCEL ; 
 int MENU_NORMAL_WINDOW ; 
 int /*<<< orphan*/  ROFI_ORIENTATION_VERTICAL ; 
 int /*<<< orphan*/  TICK () ; 
 int /*<<< orphan*/  TICK_N (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  WIDGET (int /*<<< orphan*/ ) ; 
 TYPE_1__* __rofi_view_state_create () ; 
 int /*<<< orphan*/  box_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_list_free_full (TYPE_2__*,int /*<<< orphan*/  (*) (char*)) ; 
 TYPE_2__* g_list_next (TYPE_2__ const*) ; 
 scalar_t__ g_malloc0_n (int /*<<< orphan*/ ,int) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listview_set_fixed_num_lines (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode_get_display_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_get_num_entries (int /*<<< orphan*/ *) ; 
 TYPE_2__* rofi_theme_get_list (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  rofi_view_add_widget (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  rofi_view_calculate_height (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_calculate_window_position (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_calculate_window_width (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_refilter (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_set_window_title (char*) ; 
 int /*<<< orphan*/  rofi_view_update (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rofi_view_window_update_size (TYPE_1__*) ; 
 int /*<<< orphan*/  sn_launchee_context_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  textbox_cursor_end (scalar_t__) ; 
 int /*<<< orphan*/  textbox_text (scalar_t__,char const*) ; 
 int /*<<< orphan*/  widget_queue_redraw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* xcb ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_map_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

RofiViewState *rofi_view_create ( Mode *sw,
                                  const char *input,
                                  MenuFlags menu_flags,
                                  void ( *finalize )( RofiViewState * ) )
{
    TICK ();
    RofiViewState *state = __rofi_view_state_create ();
    state->menu_flags    = menu_flags;
    state->sw            = sw;
    state->selected_line = UINT32_MAX;
    state->retv          = MENU_CANCEL;
    state->distance      = NULL;
    state->quit          = FALSE;
    state->skip_absorb   = FALSE;
    //We want to filter on the first run.
    state->refilter   = TRUE;
    state->finalize   = finalize;
    state->mouse_seen = FALSE;

    // Request the lines to show.
    state->num_lines = mode_get_num_entries ( sw );

    if ( state->sw ) {
        char * title = g_strdup_printf ( "rofi - %s", mode_get_display_name (state->sw ) );
        rofi_view_set_window_title ( title );
        g_free ( title );
    } else {
        rofi_view_set_window_title ( "rofi" );
    }
    TICK_N ( "Startup notification" );

    // Get active monitor size.
    TICK_N ( "Get active monitor" );

    state->main_window = box_create ( NULL, "window", ROFI_ORIENTATION_VERTICAL );
    // Get children.
    GList *list = rofi_theme_get_list ( WIDGET ( state->main_window ), "children", "mainbox" );
    for ( const GList *iter = list; iter != NULL; iter = g_list_next ( iter ) ) {
        rofi_view_add_widget ( state, WIDGET ( state->main_window ), (const char *) iter->data );
    }
    g_list_free_full ( list, g_free );

    if ( state->text && input ) {
        textbox_text ( state->text, input );
        textbox_cursor_end ( state->text );
    }


    // filtered list
    state->line_map = g_malloc0_n ( state->num_lines, sizeof ( unsigned int ) );
    state->distance = (int *) g_malloc0_n ( state->num_lines, sizeof ( int ) );

    rofi_view_calculate_window_width ( state );
    // Need to resize otherwise calculated desired height is wrong.
    widget_resize ( WIDGET ( state->main_window ), state->width, 100 );
    // Only needed when window is fixed size.
    if ( ( CacheState.flags & MENU_NORMAL_WINDOW ) == MENU_NORMAL_WINDOW ) {
        listview_set_fixed_num_lines ( state->list_view );
    }

    state->height = rofi_view_calculate_height ( state );
    // Move the window to the correct x,y position.
    rofi_view_calculate_window_position ( state );
    rofi_view_window_update_size ( state );

    state->quit = FALSE;
    rofi_view_refilter ( state );
    rofi_view_update ( state, TRUE );
    xcb_map_window ( xcb->connection, CacheState.main_window );
    widget_queue_redraw ( WIDGET ( state->main_window ) );
    xcb_flush ( xcb->connection );
    if ( xcb->sncontext != NULL ) {
        sn_launchee_context_complete ( xcb->sncontext );
    }
    return state;
}