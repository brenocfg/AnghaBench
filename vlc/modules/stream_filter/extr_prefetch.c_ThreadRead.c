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
struct TYPE_4__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ stream_sys_t ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_stream_ReadPartial (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static ssize_t ThreadRead(stream_t *stream, void *buf, size_t length)
{
    stream_sys_t *sys = stream->p_sys;
    int canc = vlc_savecancel();

    vlc_mutex_unlock(&sys->lock);
    assert(length > 0);

    ssize_t val = vlc_stream_ReadPartial(stream->s, buf, length);

    vlc_mutex_lock(&sys->lock);
    vlc_restorecancel(canc);
    return val;
}