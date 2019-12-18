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
struct TYPE_4__ {int /*<<< orphan*/ * module; } ;
typedef  int /*<<< orphan*/  GModule ;

/* Variables and functions */
 TYPE_1__** available_modi ; 
 int /*<<< orphan*/  g_free (TYPE_1__**) ; 
 int /*<<< orphan*/  g_module_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_free (TYPE_1__**) ; 
 unsigned int num_available_modi ; 

__attribute__((used)) static void rofi_collect_modi_destroy ( void )
{
    for  ( unsigned int i = 0; i < num_available_modi; i++ ) {
        if ( available_modi[i]->module ) {
            GModule *mod = available_modi[i]->module;
            available_modi[i] = NULL;
            g_module_close ( mod );
        }
        if ( available_modi[i] ) {
            mode_free ( &( available_modi[i] ) );
        }
    }
    g_free ( available_modi );
    available_modi     = NULL;
    num_available_modi = 0;
}