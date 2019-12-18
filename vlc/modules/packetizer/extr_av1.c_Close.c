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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_1__ decoder_t ;
typedef  int /*<<< orphan*/  av1_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  PacketizeFlush (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close(vlc_object_t *p_this)
{
    decoder_t *p_dec = (decoder_t*)p_this;
    av1_sys_t *p_sys = p_dec->p_sys;

    PacketizeFlush(p_dec);

    free(p_sys);
}