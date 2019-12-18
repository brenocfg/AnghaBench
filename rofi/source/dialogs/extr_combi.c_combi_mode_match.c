#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rofi_int_matcher ;
struct TYPE_5__ {unsigned int num_switchers; unsigned int* starts; unsigned int* lengths; TYPE_1__* switchers; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; scalar_t__ disable; } ;
typedef  int /*<<< orphan*/  Mode ;
typedef  TYPE_2__ CombiModePrivateData ;

/* Variables and functions */
 TYPE_2__* mode_get_private_data (int /*<<< orphan*/  const*) ; 
 int mode_token_match (int /*<<< orphan*/ ,int /*<<< orphan*/ **,unsigned int) ; 

__attribute__((used)) static int combi_mode_match ( const Mode *sw, rofi_int_matcher **tokens, unsigned int index )
{
    CombiModePrivateData *pd = mode_get_private_data ( sw );
    for ( unsigned i = 0; i < pd->num_switchers; i++ ) {
        if ( pd->switchers[i].disable ) {
            continue;
        }
        if ( index >= pd->starts[i] && index < ( pd->starts[i] + pd->lengths[i] ) ) {
            return mode_token_match ( pd->switchers[i].mode, tokens, index - pd->starts[i] );
        }
    }
    return 0;
}