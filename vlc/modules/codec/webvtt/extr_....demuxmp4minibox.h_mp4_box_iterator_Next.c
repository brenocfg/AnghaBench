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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int i_buffer; size_t i_payload; int /*<<< orphan*/ * p_buffer; int /*<<< orphan*/ * p_payload; int /*<<< orphan*/  i_type; } ;
typedef  TYPE_1__ mp4_box_iterator_t ;

/* Variables and functions */
 size_t GetDWBE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  VLC_FOURCC (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static bool mp4_box_iterator_Next( mp4_box_iterator_t *p_it )
{
    while( p_it->i_buffer > 8 )
    {
        const uint8_t *p = p_it->p_buffer;
        const size_t i_size = GetDWBE( p );
        p_it->i_type = VLC_FOURCC(p[4], p[5], p[6], p[7]);
        if( i_size >= 8 && i_size <= p_it->i_buffer )
        {
            p_it->p_payload = &p_it->p_buffer[8];
            p_it->i_payload = i_size - 8;
            /* update for next run */
            p_it->p_buffer += i_size;
            p_it->i_buffer -= i_size;
            return true;
        }
        else break;
    }
    return false;
}