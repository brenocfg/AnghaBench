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
typedef  int /*<<< orphan*/  rofi_int_matcher ;
struct TYPE_2__ {int /*<<< orphan*/ * messages; } ;
typedef  int /*<<< orphan*/  Mode ;
typedef  TYPE_1__ KeysHelpModePrivateData ;

/* Variables and functions */
 int helper_token_match (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ mode_get_private_data (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int help_keys_token_match ( const Mode *data,
                                   rofi_int_matcher **tokens,
                                   unsigned int index
                                   )
{
    KeysHelpModePrivateData *rmpd = (KeysHelpModePrivateData *) mode_get_private_data ( data );
    return helper_token_match ( tokens, rmpd->messages[index] );
}