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
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_5__ {int /*<<< orphan*/  resource; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/ * vlc_http_live_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *LiveRead(stream_t *access, bool *restrict eof)
{
    access_sys_t *sys = access->p_sys;

    block_t *b = vlc_http_live_read(sys->resource);
    if (b == NULL) /* TODO: loop instead of EOF, see vlc_http_live_read() */
        *eof = true;
    return b;
}