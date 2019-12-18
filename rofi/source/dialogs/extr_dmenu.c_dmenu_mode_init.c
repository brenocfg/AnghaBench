#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char gchar ;
struct TYPE_7__ {int location; int case_sensitive; int /*<<< orphan*/  menu_lines; } ;
struct TYPE_6__ {char* display_name; } ;
struct TYPE_5__ {char separator; char* message; char* format; char* column_separator; int /*<<< orphan*/  columns; int /*<<< orphan*/  input_stream; int /*<<< orphan*/  data_input_stream; int /*<<< orphan*/  cancel; int /*<<< orphan*/  cancel_source; int /*<<< orphan*/  num_active_list; int /*<<< orphan*/  active_list; int /*<<< orphan*/  num_urgent_list; int /*<<< orphan*/  urgent_list; int /*<<< orphan*/  selected_line; } ;
typedef  int /*<<< orphan*/  Mode ;
typedef  TYPE_1__ DmenuModePrivateData ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int STDIN_FILENO ; 
 int TRUE ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  async_read_cancel ; 
 TYPE_4__ config ; 
 TYPE_3__ dmenu_mode ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ find_arg (char*) ; 
 int /*<<< orphan*/  find_arg_char (char*,char*) ; 
 scalar_t__ find_arg_str (char*,char**) ; 
 int /*<<< orphan*/  find_arg_uint (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_cancellable_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_cancellable_new () ; 
 int /*<<< orphan*/  g_data_input_stream_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_malloc0 (int) ; 
 char* g_markup_printf_escaped (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strsplit (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_unix_input_stream_new (int,int) ; 
 int isatty (int) ; 
 int /*<<< orphan*/ * mode_get_private_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_set_private_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_ranges (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* rofi_expand_path (char*) ; 
 int /*<<< orphan*/  rofi_view_error_dialog (char*,int) ; 

__attribute__((used)) static int dmenu_mode_init ( Mode *sw )
{
    if ( mode_get_private_data ( sw ) != NULL ) {
        return TRUE;
    }
    mode_set_private_data ( sw, g_malloc0 ( sizeof ( DmenuModePrivateData ) ) );
    DmenuModePrivateData *pd = (DmenuModePrivateData *) mode_get_private_data ( sw );

    pd->separator     = '\n';
    pd->selected_line = UINT32_MAX;

    find_arg_str ( "-mesg", &( pd->message ) );

    // Input data separator.
    find_arg_char ( "-sep", &( pd->separator ) );

    find_arg_uint (  "-selected-row", &( pd->selected_line ) );
    // By default we print the unescaped line back.
    pd->format = "s";

    // Allow user to override the output format.
    find_arg_str ( "-format", &( pd->format ) );
    // Urgent.
    char *str = NULL;
    find_arg_str (  "-u", &str );
    if ( str != NULL ) {
        parse_ranges ( str, &( pd->urgent_list ), &( pd->num_urgent_list ) );
    }
    // Active
    str = NULL;
    find_arg_str (  "-a", &str );
    if ( str != NULL ) {
        parse_ranges ( str, &( pd->active_list ), &( pd->num_active_list ) );
    }

    // DMENU COMPATIBILITY
    find_arg_uint (  "-l", &( config.menu_lines ) );

    str = NULL;
    find_arg_str ( "-window-title", &str );
    if ( str ) {
        dmenu_mode.display_name = str;
    }

    /**
     * Dmenu compatibility.
     * `-b` put on bottom.
     */
    if ( find_arg ( "-b" ) >= 0 ) {
        config.location = 6;
    }
    /* -i case insensitive */
    config.case_sensitive = TRUE;
    if ( find_arg ( "-i" ) >= 0 ) {
        config.case_sensitive = FALSE;
    }
    int fd = STDIN_FILENO;
    str = NULL;
    if ( find_arg_str ( "-input", &str ) ) {
        char *estr = rofi_expand_path ( str );
        fd = open ( str, O_RDONLY );
        if ( fd < 0 ) {
            char *msg = g_markup_printf_escaped ( "Failed to open file: <b>%s</b>:\n\t<i>%s</i>", estr, g_strerror ( errno ) );
            rofi_view_error_dialog ( msg, TRUE );
            g_free ( msg );
            g_free ( estr );
            return TRUE;
        }
        g_free ( estr );
    }
    // If input is stdin, and a tty, do not read as rofi grabs input and therefor blocks.
    if ( !( fd == STDIN_FILENO && isatty ( fd ) == 1 ) ) {
        pd->cancel            = g_cancellable_new ();
        pd->cancel_source     = g_cancellable_connect ( pd->cancel, G_CALLBACK ( async_read_cancel ), pd, NULL );
        pd->input_stream      = g_unix_input_stream_new ( fd, fd != STDIN_FILENO );
        pd->data_input_stream = g_data_input_stream_new ( pd->input_stream );
    }
    gchar *columns = NULL;
    if ( find_arg_str ( "-display-columns", &columns ) ) {
        pd->columns          = g_strsplit ( columns, ",", 0 );
        pd->column_separator = "\t";
        find_arg_str ( "-display-column-separator", &pd->column_separator );
    }
    return TRUE;
}