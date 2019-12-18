#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int messages_length; } ;
typedef  int /*<<< orphan*/  Mode ;
typedef  TYPE_1__ KeysHelpModePrivateData ;

/* Variables and functions */
 scalar_t__ mode_get_private_data (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static unsigned int help_keys_mode_get_num_entries ( const Mode *sw )
{
    const KeysHelpModePrivateData *pd = (const KeysHelpModePrivateData *) mode_get_private_data ( sw );
    return pd->messages_length;
}