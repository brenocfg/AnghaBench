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
struct TYPE_4__ {int /*<<< orphan*/  p_input_item; } ;
typedef  TYPE_1__ libvlc_media_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 char* input_item_GetURI (int /*<<< orphan*/ ) ; 

char *
libvlc_media_get_mrl( libvlc_media_t * p_md )
{
    assert( p_md );
    return input_item_GetURI( p_md->p_input_item );
}