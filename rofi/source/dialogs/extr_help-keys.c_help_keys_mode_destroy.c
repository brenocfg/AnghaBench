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
struct TYPE_3__ {int /*<<< orphan*/  messages; } ;
typedef  int /*<<< orphan*/  Mode ;
typedef  TYPE_1__ KeysHelpModePrivateData ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_strfreev (int /*<<< orphan*/ ) ; 
 scalar_t__ mode_get_private_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mode_set_private_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void help_keys_mode_destroy ( Mode *sw )
{
    KeysHelpModePrivateData *rmpd = (KeysHelpModePrivateData *) mode_get_private_data ( sw );
    if ( rmpd != NULL ) {
        g_strfreev ( rmpd->messages );
        g_free ( rmpd );
        mode_set_private_data ( sw, NULL );
    }
}