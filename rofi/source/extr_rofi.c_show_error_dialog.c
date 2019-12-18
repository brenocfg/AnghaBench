#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ data; } ;
struct TYPE_11__ {char* str; } ;
typedef  TYPE_1__ GString ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_MSG_MARKUP ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* g_list_first (int /*<<< orphan*/ ) ; 
 int g_list_length (TYPE_2__*) ; 
 TYPE_2__* g_list_next (TYPE_2__*) ; 
 int /*<<< orphan*/  g_string_append (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  g_string_append_printf (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  g_string_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_string_new (char*) ; 
 int /*<<< orphan*/  list_of_error_msgs ; 
 int /*<<< orphan*/  rofi_set_return_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rofi_view_error_dialog (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_error_dialog ()
{
    GString *emesg = g_string_new ( "The following errors were detected when starting rofi:\n" );
    GList   *iter  = g_list_first ( list_of_error_msgs );
    int     index  = 0;
    for (; iter != NULL && index < 2; iter = g_list_next ( iter ) ) {
        GString *msg = (GString *) ( iter->data );
        g_string_append ( emesg, "\n\n" );
        g_string_append ( emesg, msg->str );
        index++;
    }
    if ( g_list_length ( iter ) > 1 ) {
        g_string_append_printf ( emesg, "\nThere are <b>%d</b> more errors.", g_list_length ( iter ) - 1 );
    }
    rofi_view_error_dialog ( emesg->str, ERROR_MSG_MARKUP );
    g_string_free ( emesg, TRUE );
    rofi_set_return_code ( EX_DATAERR );

}