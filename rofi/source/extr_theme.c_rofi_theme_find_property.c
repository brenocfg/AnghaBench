#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gboolean ;
struct TYPE_11__ {struct TYPE_11__* parent; int /*<<< orphan*/  name; scalar_t__ properties; } ;
typedef  TYPE_3__ ThemeWidget ;
struct TYPE_9__ {TYPE_4__* ref; } ;
struct TYPE_10__ {TYPE_1__ link; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_2__ value; } ;
typedef  scalar_t__ PropertyType ;
typedef  TYPE_4__ Property ;

/* Variables and functions */
 scalar_t__ P_INHERIT ; 
 scalar_t__ P_INTEGER ; 
 scalar_t__ P_LINK ; 
 scalar_t__ P_PADDING ; 
 int /*<<< orphan*/ * PropertyTypeName ; 
 int /*<<< orphan*/  g_debug (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_contains (scalar_t__,char const*) ; 
 TYPE_4__* g_hash_table_lookup (scalar_t__,char const*) ; 
 int /*<<< orphan*/  rofi_theme_resolve_link_property (TYPE_4__*,int /*<<< orphan*/ ) ; 

Property *rofi_theme_find_property ( ThemeWidget *widget, PropertyType type, const char *property, gboolean exact )
{
    while ( widget ) {
        if ( widget->properties && g_hash_table_contains ( widget->properties, property ) ) {
            Property *p = g_hash_table_lookup ( widget->properties, property );
            if ( p->type == P_INHERIT ) {
                return p;
            }
            if ( p->type == P_LINK ) {
                if ( p->value.link.ref == NULL ) {
                    // Resolve link.
                    rofi_theme_resolve_link_property ( p, 0 );
                }
                if ( p->value.link.ref != NULL && p->value.link.ref->type == type ) {
                    return p->value.link.ref;
                }
            }
            if ( p->type == type ) {
                return p;
            }
            // RofiPadding and integer can be converted.
            if ( p->type == P_INTEGER && type == P_PADDING ) {
                return p;
            }
            g_debug ( "Found property: '%s' on '%s', but type %s does not match expected type %s.",
                      property, widget->name,
                      PropertyTypeName[p->type],
                      PropertyTypeName[type]
                      );
        }
        if ( exact ) {
            return NULL;
        }
        // Fall back to defaults.
        widget = widget->parent;
    }
    return NULL;
}