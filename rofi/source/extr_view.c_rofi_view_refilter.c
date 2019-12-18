#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  callback; } ;
struct TYPE_16__ {unsigned int start; int count; unsigned int* acount; char* pattern; TYPE_2__ st; int /*<<< orphan*/  plen; int /*<<< orphan*/ * mutex; int /*<<< orphan*/ * cond; int /*<<< orphan*/  stop; TYPE_4__* state; } ;
typedef  TYPE_3__ thread_state_view ;
typedef  int /*<<< orphan*/  glong ;
typedef  char gchar ;
struct TYPE_17__ {int num_lines; unsigned int* line_map; unsigned int filtered_lines; unsigned int selected_line; int height; void* refilter; scalar_t__ quit; int /*<<< orphan*/  retv; int /*<<< orphan*/  list_view; scalar_t__ tb_total_rows; scalar_t__ tb_filtered_rows; int /*<<< orphan*/  distance; int /*<<< orphan*/ * tokens; TYPE_1__* text; int /*<<< orphan*/  sw; void* reload; } ;
struct TYPE_14__ {int /*<<< orphan*/  text; } ;
struct TYPE_13__ {scalar_t__ auto_select; scalar_t__ sort; int /*<<< orphan*/  case_sensitive; } ;
typedef  TYPE_4__ RofiViewState ;
typedef  int /*<<< orphan*/  GMutex ;
typedef  int /*<<< orphan*/  GCond ;

/* Variables and functions */
 void* FALSE ; 
 unsigned int MAX (int,int) ; 
 int /*<<< orphan*/  MENU_OK ; 
 int /*<<< orphan*/  MIN (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  TICK_N (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _rofi_view_reload_row (TYPE_4__*) ; 
 TYPE_11__ config ; 
 int /*<<< orphan*/  filter_elements ; 
 int /*<<< orphan*/  g_cond_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_mutex_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_qsort_with_data (unsigned int*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* g_strdup_printf (char*,unsigned int) ; 
 int /*<<< orphan*/  g_thread_pool_push (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_utf8_strlen (char*,int) ; 
 int /*<<< orphan*/ * helper_tokenize (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  helper_tokenize_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lev_sort ; 
 size_t listview_get_selected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listview_set_num_elements (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memmove (unsigned int*,unsigned int*,int) ; 
 char* mode_preprocess_input (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rofi_view_calculate_height (TYPE_4__*) ; 
 int /*<<< orphan*/  rofi_view_calculate_window_position (TYPE_4__*) ; 
 int /*<<< orphan*/  rofi_view_call_thread (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rofi_view_window_update_size (TYPE_4__*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textbox_text (scalar_t__,char*) ; 
 int /*<<< orphan*/  tpool ; 

__attribute__((used)) static void rofi_view_refilter ( RofiViewState *state )
{
    TICK_N ( "Filter start" );
    if ( state->reload ) {
        _rofi_view_reload_row ( state );
        state->reload = FALSE;
    }
    if ( state->tokens ) {
        helper_tokenize_free ( state->tokens );
        state->tokens = NULL;
    }
    if ( state->text && strlen ( state->text->text ) > 0 ) {
        unsigned int j        = 0;
        gchar        *pattern = mode_preprocess_input ( state->sw, state->text->text );
        glong        plen     = pattern ? g_utf8_strlen ( pattern, -1 ) : 0;
        state->tokens = helper_tokenize ( pattern, config.case_sensitive );
        /**
         * On long lists it can be beneficial to parallelize.
         * If number of threads is 1, no thread is spawn.
         * If number of threads > 1 and there are enough (> 1000) items, spawn jobs for the thread pool.
         * For large lists with 8 threads I see a factor three speedup of the whole function.
         */
        unsigned int      nt = MAX ( 1, state->num_lines / 500 );
        thread_state_view states[nt];
        GCond             cond;
        GMutex            mutex;
        g_mutex_init ( &mutex );
        g_cond_init ( &cond );
        unsigned int count = nt;
        unsigned int steps = ( state->num_lines + nt ) / nt;
        for ( unsigned int i = 0; i < nt; i++ ) {
            states[i].state       = state;
            states[i].start       = i * steps;
            states[i].stop        = MIN ( state->num_lines, ( i + 1 ) * steps );
            states[i].count       = 0;
            states[i].cond        = &cond;
            states[i].mutex       = &mutex;
            states[i].acount      = &count;
            states[i].plen        = plen;
            states[i].pattern     = pattern;
            states[i].st.callback = filter_elements;
            if ( i > 0 ) {
                g_thread_pool_push ( tpool, &states[i], NULL );
            }
        }
        // Run one in this thread.
        rofi_view_call_thread ( &states[0], NULL );
        // No need to do this with only one thread.
        if ( nt > 1 ) {
            g_mutex_lock ( &mutex );
            while ( count > 0 ) {
                g_cond_wait ( &cond, &mutex );
            }
            g_mutex_unlock ( &mutex );
        }
        g_cond_clear ( &cond );
        g_mutex_clear ( &mutex );
        for ( unsigned int i = 0; i < nt; i++ ) {
            if ( j != states[i].start ) {
                memmove ( &( state->line_map[j] ), &( state->line_map[states[i].start] ), sizeof ( unsigned int ) * ( states[i].count ) );
            }
            j += states[i].count;
        }
        if ( config.sort ) {
            g_qsort_with_data ( state->line_map, j, sizeof ( int ), lev_sort, state->distance );
        }

        // Cleanup + bookkeeping.
        state->filtered_lines = j;
        g_free ( pattern );
    }
    else{
        for ( unsigned int i = 0; i < state->num_lines; i++ ) {
            state->line_map[i] = i;
        }
        state->filtered_lines = state->num_lines;
    }
    listview_set_num_elements ( state->list_view, state->filtered_lines );

    if ( state->tb_filtered_rows ) {
        char *r = g_strdup_printf("%u", state->filtered_lines);
        textbox_text( state->tb_filtered_rows, r );
        g_free(r);
    }
    if ( state->tb_total_rows )  {
        char *r = g_strdup_printf("%u", state->num_lines);
        textbox_text( state->tb_total_rows, r );
        g_free(r);
    }



    if ( config.auto_select == TRUE && state->filtered_lines == 1 && state->num_lines > 1 ) {
        ( state->selected_line ) = state->line_map[listview_get_selected ( state->list_view  )];
        state->retv              = MENU_OK;
        state->quit              = TRUE;
    }
    // Size the window.
    int height = rofi_view_calculate_height ( state );
    if ( height != state->height ) {
        state->height = height;
        rofi_view_calculate_window_position ( state );
        rofi_view_window_update_size ( state );
        g_debug ( "Resize based on re-filter" );
    }
    state->refilter = FALSE;
    TICK_N ( "Filter done" );
}