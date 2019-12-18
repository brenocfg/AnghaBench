#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rofi_int_matcher ;
struct TYPE_13__ {char* filter; int /*<<< orphan*/  case_sensitive; scalar_t__ auto_select; } ;
struct TYPE_12__ {char* display_name; scalar_t__ private_data; } ;
struct TYPE_11__ {unsigned int cmd_list_length; int only_selected; int multi_select; int do_markup; unsigned int selected_line; int /*<<< orphan*/ * cancel; int /*<<< orphan*/  format; TYPE_1__* cmd_list; } ;
struct TYPE_10__ {int /*<<< orphan*/  entry; } ;
typedef  int /*<<< orphan*/  RofiViewState ;
typedef  int /*<<< orphan*/  MenuFlags ;
typedef  TYPE_1__ DmenuScriptEntry ;
typedef  TYPE_2__ DmenuModePrivateData ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  MENU_INDICATOR ; 
 int /*<<< orphan*/  MENU_NORMAL ; 
 int /*<<< orphan*/  MENU_PASSWORD ; 
 int TRUE ; 
 TYPE_9__ config ; 
 int /*<<< orphan*/  dmenu_finalize ; 
 TYPE_3__ dmenu_mode ; 
 int /*<<< orphan*/  dmenu_mode_free (TYPE_3__*) ; 
 scalar_t__ find_arg (char*) ; 
 int /*<<< orphan*/  find_arg_str (char*,char**) ; 
 int /*<<< orphan*/  find_arg_uint (char*,unsigned int*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (char*) ; 
 int get_dmenu_async (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  get_dmenu_sync (TYPE_2__*) ; 
 scalar_t__ helper_token_match (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** helper_tokenize (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  helper_tokenize_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mode_init (TYPE_3__*) ; 
 int /*<<< orphan*/  rofi_output_formatted_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,char*) ; 
 int /*<<< orphan*/ * rofi_view_create (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rofi_view_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rofi_view_set_overlay (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rofi_view_set_selected_line (int /*<<< orphan*/ *,unsigned int) ; 

int dmenu_switcher_dialog ( void )
{
    mode_init ( &dmenu_mode );
    MenuFlags            menu_flags = MENU_NORMAL;
    DmenuModePrivateData *pd        = (DmenuModePrivateData *) dmenu_mode.private_data;
    int                  async      = TRUE;

    // For now these only work in sync mode.
    if ( find_arg ( "-sync" ) >= 0 || find_arg ( "-dump" ) >= 0 || find_arg ( "-select" ) >= 0
         || find_arg ( "-no-custom" ) >= 0 || find_arg ( "-only-match" ) >= 0 || config.auto_select ||
         find_arg ( "-selected-row" ) >= 0 ) {
        async = FALSE;
    }
    // Check if the subsystem is setup for reading, otherwise do not read.
    if ( pd->cancel != NULL ) {
        if ( async ) {
            unsigned int pre_read = 25;
            find_arg_uint ( "-async-pre-read", &pre_read );
            async = get_dmenu_async ( pd, pre_read );
        }
        else {
            get_dmenu_sync ( pd );
        }
    }
    char         *input          = NULL;
    unsigned int cmd_list_length = pd->cmd_list_length;
    DmenuScriptEntry *cmd_list     = pd->cmd_list;

    pd->only_selected = FALSE;
    pd->multi_select  = FALSE;
    if ( find_arg ( "-multi-select" ) >= 0 ) {
        menu_flags       = MENU_INDICATOR;
        pd->multi_select = TRUE;
    }
    if ( find_arg ( "-markup-rows" ) >= 0 ) {
        pd->do_markup = TRUE;
    }
    if ( find_arg ( "-only-match" ) >= 0 || find_arg ( "-no-custom" ) >= 0 ) {
        pd->only_selected = TRUE;
        if ( cmd_list_length == 0 ) {
            return TRUE;
        }
    }
    if ( config.auto_select && cmd_list_length == 1 ) {
        rofi_output_formatted_line ( pd->format, cmd_list[0].entry , 0, config.filter );
        return TRUE;
    }
    if ( find_arg ( "-password" ) >= 0 ) {
        menu_flags |= MENU_PASSWORD;
    }
    /* copy filter string */
    input = g_strdup ( config.filter );

    char *select = NULL;
    find_arg_str ( "-select", &select );
    if ( select != NULL ) {
        rofi_int_matcher **tokens = helper_tokenize ( select, config.case_sensitive );
        unsigned int     i        = 0;
        for ( i = 0; i < cmd_list_length; i++ ) {
            if ( helper_token_match ( tokens, cmd_list[i].entry ) ) {
                pd->selected_line = i;
                break;
            }
        }
        helper_tokenize_free ( tokens );
    }
    if ( find_arg ( "-dump" ) >= 0 ) {
        rofi_int_matcher **tokens = helper_tokenize ( config.filter ? config.filter : "", config.case_sensitive );
        unsigned int     i        = 0;
        for ( i = 0; i < cmd_list_length; i++ ) {
            if ( tokens == NULL || helper_token_match ( tokens, cmd_list[i].entry ) ) {
                rofi_output_formatted_line ( pd->format, cmd_list[i].entry , i, config.filter );
            }
        }
        helper_tokenize_free ( tokens );
        dmenu_mode_free ( &dmenu_mode );
        g_free ( input );
        return TRUE;
    }
    find_arg_str (  "-p", &( dmenu_mode.display_name ) );
    RofiViewState *state = rofi_view_create ( &dmenu_mode, input, menu_flags, dmenu_finalize );
    // @TODO we should do this better.
    if ( async && ( pd->cancel != NULL ) ) {
        rofi_view_set_overlay ( state, "Loading.. " );
    }
    rofi_view_set_selected_line ( state, pd->selected_line );
    rofi_view_set_active ( state );

    return FALSE;
}