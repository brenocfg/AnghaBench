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
typedef  size_t gsize ;
struct TYPE_4__ {int /*<<< orphan*/  comment; int /*<<< orphan*/  binding; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ActionBindingEntry ;

/* Variables and functions */
 size_t G_N_ELEMENTS (TYPE_1__*) ; 
 int /*<<< orphan*/  config_parser_add_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ ) ; 
 TYPE_1__* rofi_bindings ; 
 int /*<<< orphan*/  xrm_String ; 

void setup_abe ( void )
{
    for ( gsize i = 0; i < G_N_ELEMENTS ( rofi_bindings ); ++i ) {
        ActionBindingEntry *b = &rofi_bindings[i];
        b->binding = g_strdup ( b->binding );
        config_parser_add_option ( xrm_String, b->name, (void * *) &( b->binding ), b->comment );
    }
}