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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  b_seek; } ;
typedef  TYPE_2__ stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int vlc_stream_Seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Seek( stream_t *s, uint64_t offset )
{
    stream_sys_t *p_sys = s->p_sys;

    assert( p_sys->b_seek );
    return vlc_stream_Seek( s->s, offset );
}