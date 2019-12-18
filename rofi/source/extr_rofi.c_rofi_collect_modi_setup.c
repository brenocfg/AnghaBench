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

/* Variables and functions */
 int /*<<< orphan*/ * available_modi ; 
 int /*<<< orphan*/  mode_set_config (int /*<<< orphan*/ ) ; 
 unsigned int num_available_modi ; 

__attribute__((used)) static void rofi_collect_modi_setup ( void )
{
    for  ( unsigned int i = 0; i < num_available_modi; i++ ) {
        mode_set_config ( available_modi[i] );
    }
}