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
struct TYPE_3__ {int /*<<< orphan*/  p_input_item; } ;
typedef  TYPE_1__ libvlc_media_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_item_AddOption (int /*<<< orphan*/ ,char const*,unsigned int) ; 

void libvlc_media_add_option_flag( libvlc_media_t * p_md,
                                   const char * ppsz_option,
                                   unsigned i_flags )
{
    input_item_AddOption( p_md->p_input_item, ppsz_option, i_flags );
}