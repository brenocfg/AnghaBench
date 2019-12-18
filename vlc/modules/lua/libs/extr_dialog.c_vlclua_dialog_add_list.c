#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ extension_widget_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENSION_WIDGET_LIST ; 
 TYPE_1__* calloc (int,int) ; 
 int vlclua_create_widget_inner (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int vlclua_dialog_add_list( lua_State *L )
{
    extension_widget_t *p_widget = calloc( 1, sizeof( extension_widget_t ) );
    p_widget->type = EXTENSION_WIDGET_LIST;

    return vlclua_create_widget_inner( L, 0, p_widget );
}