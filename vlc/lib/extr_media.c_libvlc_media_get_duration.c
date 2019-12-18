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
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int from_mtime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_GetDuration (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_IsPreparsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 

int64_t
libvlc_media_get_duration( libvlc_media_t * p_md )
{
    assert( p_md );

    if( !p_md->p_input_item )
    {
        libvlc_printerr( "No input item" );
        return -1;
    }

    if (!input_item_IsPreparsed( p_md->p_input_item ))
        return -1;

    return from_mtime(input_item_GetDuration( p_md->p_input_item ));
}