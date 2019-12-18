#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/ * next; scalar_t__ data; } ;
struct TYPE_12__ {char* name; TYPE_7__* def_value; } ;
struct TYPE_17__ {int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; } ;
struct TYPE_15__ {double red; double green; double blue; double alpha; } ;
struct TYPE_13__ {double red; double green; double blue; double alpha; } ;
struct TYPE_14__ {int style; TYPE_2__ color; } ;
struct TYPE_16__ {size_t i; char* s; double f; TYPE_1__ link; TYPE_6__ padding; TYPE_4__ color; int /*<<< orphan*/  b; TYPE_3__ highlight; TYPE_8__* list; } ;
struct TYPE_18__ {int type; TYPE_5__ value; } ;
typedef  TYPE_7__ Property ;
typedef  TYPE_8__ GList ;

/* Variables and functions */
#define  P_BOOLEAN 139 
#define  P_COLOR 138 
#define  P_DOUBLE 137 
#define  P_HIGHLIGHT 136 
#define  P_INHERIT 135 
#define  P_INTEGER 134 
#define  P_LINK 133 
#define  P_LIST 132 
#define  P_ORIENTATION 131 
#define  P_PADDING 130 
#define  P_POSITION 129 
#define  P_STRING 128 
 int ROFI_HL_BOLD ; 
 int ROFI_HL_COLOR ; 
 int ROFI_HL_ITALIC ; 
 int ROFI_HL_STRIKETHROUGH ; 
 int ROFI_HL_UNDERLINE ; 
 size_t ROFI_ORIENTATION_HORIZONTAL ; 
 char** WindowLocationStr ; 
 int /*<<< orphan*/  distance_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* g_list_next (TYPE_8__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rofi_theme_print_distance (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void int_rofi_theme_print_property ( Property *p )
{
    switch ( p->type )
    {
        case P_LIST:
            printf ( "[ " );
            for ( GList *iter = p->value.list; iter != NULL; iter = g_list_next ( iter ) ) {
                printf ( "%s", (char *) ( iter->data ) );
                if ( iter->next != NULL ) {
                    printf ( "," );
                }
            }
            printf ( " ]" );
            break;
        case P_ORIENTATION:
            printf ( "%s", ( p->value.i == ROFI_ORIENTATION_HORIZONTAL ) ? "horizontal" : "vertical" );
            break;
        case P_HIGHLIGHT:
            if ( p->value.highlight.style & ROFI_HL_BOLD ) {
                printf ( "bold " );
            }
            if ( p->value.highlight.style & ROFI_HL_UNDERLINE ) {
                printf ( "underline " );
            }
            if ( p->value.highlight.style & ROFI_HL_STRIKETHROUGH ) {
                printf ( "strikethrough " );
            }
            if ( p->value.highlight.style & ROFI_HL_ITALIC ) {
                printf ( "italic " );
            }
            if ( p->value.highlight.style & ROFI_HL_COLOR ) {
                printf ( "rgba ( %.0f, %.0f, %.0f, %.0f %% )",
                        ( p->value.highlight.color.red * 255.0 ),
                        ( p->value.highlight.color.green * 255.0 ),
                        ( p->value.highlight.color.blue * 255.0 ),
                        ( p->value.highlight.color.alpha * 100.0 ) );
            }
            break;
        case P_POSITION:
            printf ( "%s", WindowLocationStr[p->value.i] );
            break;
        case P_STRING:
            printf ( "\"%s\"", p->value.s );
            break;
        case P_INTEGER:
            printf ( "%d", p->value.i );
            break;
        case P_DOUBLE:
            printf ( "%.2f", p->value.f );
            break;
        case P_BOOLEAN:
            printf ( "%s", p->value.b ? "true" : "false" );
            break;
        case P_COLOR:
            printf ( "rgba ( %.0f, %.0f, %.0f, %.0f %% )",
                    ( p->value.color.red * 255.0 ),
                    ( p->value.color.green * 255.0 ),
                    ( p->value.color.blue * 255.0 ),
                    ( p->value.color.alpha * 100.0 ) );
            break;
        case P_PADDING:
            if ( distance_compare ( p->value.padding.top, p->value.padding.bottom ) &&
                    distance_compare ( p->value.padding.left, p->value.padding.right ) &&
                    distance_compare ( p->value.padding.left, p->value.padding.top ) ) {
                rofi_theme_print_distance ( p->value.padding.left );
            }
            else if ( distance_compare ( p->value.padding.top, p->value.padding.bottom ) &&
                    distance_compare ( p->value.padding.left, p->value.padding.right ) ) {
                rofi_theme_print_distance ( p->value.padding.top );
                rofi_theme_print_distance ( p->value.padding.left );
            }
            else if ( !distance_compare ( p->value.padding.top, p->value.padding.bottom ) &&
                    distance_compare ( p->value.padding.left, p->value.padding.right ) ) {
                rofi_theme_print_distance ( p->value.padding.top );
                rofi_theme_print_distance ( p->value.padding.left );
                rofi_theme_print_distance ( p->value.padding.bottom );
            }
            else {
                rofi_theme_print_distance ( p->value.padding.top );
                rofi_theme_print_distance ( p->value.padding.right );
                rofi_theme_print_distance ( p->value.padding.bottom );
                rofi_theme_print_distance ( p->value.padding.left );
            }
            break;
        case P_LINK:
            if ( p->value.link.def_value) {
                printf( "var( %s, ", p->value.link.name );
                int_rofi_theme_print_property ( p->value.link.def_value );
                printf (")");
            }else {
                printf ( "var(%s)", p->value.link.name );
            }
            break;
        case P_INHERIT:
            printf ( "inherit" );
            break;
        default:
            break;
    }

}