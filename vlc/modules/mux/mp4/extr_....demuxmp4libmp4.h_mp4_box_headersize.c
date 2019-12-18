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
struct TYPE_3__ {int i_shortsize; scalar_t__ i_type; } ;
typedef  TYPE_1__ MP4_Box_t ;

/* Variables and functions */
 scalar_t__ ATOM_uuid ; 

__attribute__((used)) static inline size_t mp4_box_headersize( MP4_Box_t *p_box )
{
    return 8
        + ( p_box->i_shortsize == 1 ? 8 : 0 )
        + ( p_box->i_type == ATOM_uuid ? 16 : 0 );
}