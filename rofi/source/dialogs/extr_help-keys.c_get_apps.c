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
struct TYPE_3__ {int /*<<< orphan*/  messages_length; int /*<<< orphan*/  messages; } ;
typedef  TYPE_1__ KeysHelpModePrivateData ;

/* Variables and functions */
 int /*<<< orphan*/  config_parser_return_display_help (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_apps ( KeysHelpModePrivateData *pd )
{
    pd->messages = config_parser_return_display_help ( &( pd->messages_length ) );
}