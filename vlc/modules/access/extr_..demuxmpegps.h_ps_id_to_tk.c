#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline unsigned ps_id_to_tk( unsigned i_id )
{
    assert(i_id >= 0xc0);
    if(unlikely(i_id < 0xc0))
        return 0;
    else if( i_id <= 0xff )
        return i_id - 0xc0;
    else if( (i_id & 0xff00) == 0xbd00 )
        return 256-0xC0 + (i_id & 0xff);
    else if( (i_id & 0xff00) == 0xfd00 )
        return 512-0xc0 + (i_id & 0xff);
    else
        return 768-0xc0 + (i_id & 0x07);
}