#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; int /*<<< orphan*/  display_name; int /*<<< orphan*/  cfg_name_key; } ;
typedef  TYPE_1__ Mode ;

/* Variables and functions */
 int /*<<< orphan*/  config_parser_add_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  xrm_String ; 

void mode_set_config ( Mode *mode )
{
    snprintf ( mode->cfg_name_key, 128, "display-%s", mode->name );
    config_parser_add_option ( xrm_String, mode->cfg_name_key, (void * *) &( mode->display_name ), "The display name of this browser" );
}