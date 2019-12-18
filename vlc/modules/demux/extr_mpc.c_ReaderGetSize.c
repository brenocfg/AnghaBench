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
typedef  int /*<<< orphan*/  mpc_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  stream_Size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mpc_int32_t ReaderGetSize( void *p_private )
{
    demux_t *p_demux = (demux_t*)p_private;
    return stream_Size( p_demux->s );
}