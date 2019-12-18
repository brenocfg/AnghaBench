#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_6__ {scalar_t__ (* read_cb ) (int /*<<< orphan*/ ,void*,size_t) ;int /*<<< orphan*/  opaque; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static ssize_t Read(stream_t *access, void *buf, size_t len)
{
    access_sys_t *sys = access->p_sys;

    ssize_t val = sys->read_cb(sys->opaque, buf, len);

    if (val < 0) {
        msg_Err(access, "read error");
        val = 0;
    }

    return val;
}