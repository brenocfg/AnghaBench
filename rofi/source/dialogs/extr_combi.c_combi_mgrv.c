#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;
typedef  struct TYPE_17__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ThemeWidget ;
struct TYPE_25__ {unsigned int num_switchers; unsigned int* starts; unsigned int* lengths; TYPE_1__* switchers; } ;
struct TYPE_24__ {int /*<<< orphan*/  name; } ;
struct TYPE_23__ {int /*<<< orphan*/  end_index; int /*<<< orphan*/  start_index; } ;
struct TYPE_20__ {int red; int green; int blue; } ;
struct TYPE_21__ {TYPE_2__ color; } ;
struct TYPE_22__ {TYPE_3__ value; } ;
struct TYPE_19__ {TYPE_12__* mode; } ;
struct TYPE_18__ {int /*<<< orphan*/  combi_hide_mode_prefix; } ;
struct TYPE_17__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ Property ;
typedef  TYPE_5__ PangoAttribute ;
typedef  TYPE_6__ Mode ;
typedef  int /*<<< orphan*/  GList ;
typedef  TYPE_7__ CombiModePrivateData ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PANGO_ATTR_INDEX_FROM_TEXT_BEGINNING ; 
 int /*<<< orphan*/  P_COLOR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_15__ config ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/ * g_list_append (int /*<<< orphan*/ *,TYPE_5__*) ; 
 char* g_strdup_printf (char*,char const*,char*) ; 
 char* mode_get_display_name (TYPE_12__*) ; 
 char* mode_get_display_value (TYPE_12__*,unsigned int,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 TYPE_7__* mode_get_private_data (TYPE_6__ const*) ; 
 TYPE_5__* pango_attr_foreground_new (int,int,int) ; 
 TYPE_4__* rofi_theme_find_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rofi_theme_find_widget (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static char * combi_mgrv ( const Mode *sw, unsigned int selected_line, int *state, GList **attr_list, int get_entry )
{
    CombiModePrivateData *pd = mode_get_private_data ( sw );
    if ( !get_entry ) {
        for ( unsigned i = 0; i < pd->num_switchers; i++ ) {
            if ( selected_line >= pd->starts[i] && selected_line < ( pd->starts[i] + pd->lengths[i] ) ) {
                mode_get_display_value ( pd->switchers[i].mode, selected_line - pd->starts[i], state, attr_list, FALSE );
                return NULL;
            }
        }
        return NULL;
    }
    for ( unsigned i = 0; i < pd->num_switchers; i++ ) {
        if ( selected_line >= pd->starts[i] && selected_line < ( pd->starts[i] + pd->lengths[i] ) ) {
            char       * retv;
            char       * str  = retv = mode_get_display_value ( pd->switchers[i].mode, selected_line - pd->starts[i], state, attr_list, TRUE );
            const char *dname = mode_get_display_name ( pd->switchers[i].mode );
            if ( !config.combi_hide_mode_prefix ) {
                retv = g_strdup_printf ( "%s %s", dname, str );
                g_free ( str );
            }

            if ( attr_list != NULL ) {
                ThemeWidget *wid = rofi_theme_find_widget ( sw->name, NULL, TRUE );
                Property    *p   = rofi_theme_find_property ( wid, P_COLOR, pd->switchers[i].mode->name, TRUE );
                if ( p != NULL ) {
                    PangoAttribute *pa = pango_attr_foreground_new (
                        p->value.color.red * 65535,
                        p->value.color.green * 65535,
                        p->value.color.blue * 65535 );
                    pa->start_index = PANGO_ATTR_INDEX_FROM_TEXT_BEGINNING;
                    pa->end_index   = strlen ( dname );
                    *attr_list      = g_list_append ( *attr_list, pa );
                }
            }
            return retv;
        }
    }

    return NULL;
}