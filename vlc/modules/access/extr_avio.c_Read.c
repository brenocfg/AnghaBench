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
typedef  int ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int avio_read (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static ssize_t Read(stream_t *access, void *data, size_t size)
{
    access_sys_t *sys = access->p_sys;

    int r = avio_read(sys->context, data, size);
    if (r < 0)
        r = 0;
    return r;
}