#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENSION_WIDGET_TEXT_FIELD ; 
 int vlclua_dialog_add_text_inner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int vlclua_dialog_add_text_input( lua_State *L )
{
    return vlclua_dialog_add_text_inner( L, EXTENSION_WIDGET_TEXT_FIELD );
}