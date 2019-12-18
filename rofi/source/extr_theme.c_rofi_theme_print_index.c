#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gpointer ;
struct TYPE_14__ {unsigned int num_widgets; struct TYPE_14__** widgets; int /*<<< orphan*/  properties; struct TYPE_14__* parent; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ThemeWidget ;
struct TYPE_16__ {scalar_t__ next; int /*<<< orphan*/ * prev; scalar_t__ data; } ;
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ Property ;
typedef  TYPE_3__ GList ;
typedef  int /*<<< orphan*/  GHashTableIter ;

/* Variables and functions */
 size_t MAX (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 TYPE_3__* g_list_first (TYPE_3__*) ; 
 int /*<<< orphan*/  g_list_free (TYPE_3__*) ; 
 scalar_t__ g_list_length (TYPE_3__*) ; 
 TYPE_3__* g_list_next (TYPE_3__*) ; 
 TYPE_3__* g_list_prepend (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ g_strcmp0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  rofi_theme_print_property_index (size_t,int,TYPE_2__*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rofi_theme_print_index ( ThemeWidget *widget )
{
    GHashTableIter iter;
    gpointer       key, value;
    if ( widget->properties ) {
        int         index = 0;
        GList       *list = NULL;
        ThemeWidget *w    = widget;
        while ( w ) {
            if ( g_strcmp0 ( w->name, "Root" ) == 0 ) {
                break;
            }
            list = g_list_prepend ( list, w->name );
            w    = w->parent;
        }
        if ( g_list_length ( list ) > 0 ) {
            index = 4;
            for ( GList *iter = g_list_first ( list ); iter != NULL; iter = g_list_next ( iter ) ) {
                char *name = (char *) iter->data;
                fputs ( name, stdout );
                if ( iter->prev == NULL && iter->next ) {
                    putchar ( ' ' );
                }
                else if ( iter->next ) {
                    putchar ( '.' );
                }
            }
            printf ( " {\n" );
        }
        else {
            index = 4;
            printf ( "* {\n" );
        }
        size_t property_name_length = 0;
        g_hash_table_iter_init ( &iter, widget->properties );
        while ( g_hash_table_iter_next ( &iter, &key, &value ) ) {
            Property *p = (Property *) value;
            property_name_length = MAX ( strlen ( p->name ), property_name_length );
        }
        g_hash_table_iter_init ( &iter, widget->properties );
        while ( g_hash_table_iter_next ( &iter, &key, &value ) ) {
            Property *p = (Property *) value;
            rofi_theme_print_property_index ( property_name_length, index, p );
        }
        printf ( "}\n" );
        g_list_free ( list );
    }
    for ( unsigned int i = 0; i < widget->num_widgets; i++ ) {
        rofi_theme_print_index ( widget->widgets[i] );
    }
}