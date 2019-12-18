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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct skiptags_sys_t {int dummy; } ;
struct TYPE_2__ {scalar_t__ p_sys; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  skiptags_sys_Delete (struct skiptags_sys_t*) ; 

__attribute__((used)) static void Close(vlc_object_t *obj)
{
    stream_t *stream = (stream_t *)obj;
    struct skiptags_sys_t *sys = (struct skiptags_sys_t *) stream->p_sys;

    skiptags_sys_Delete(sys);
}