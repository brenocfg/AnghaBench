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
struct TYPE_5__ {TYPE_1__* converted; } ;
typedef  TYPE_2__ libvlc_picture_t ;
struct TYPE_4__ {size_t i_buffer; unsigned char const* p_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

const unsigned char* libvlc_picture_get_buffer( const libvlc_picture_t* pic,
                                                size_t *size )
{
    assert( size != NULL );
    *size = pic->converted->i_buffer;
    return pic->converted->p_buffer;
}