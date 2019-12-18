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
struct TYPE_6__ {int /*<<< orphan*/  cache; } ;
typedef  TYPE_2__ stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AStreamPrebufferBlock (TYPE_1__*) ; 
 int /*<<< orphan*/  block_BytestreamEmpty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void AStreamControlReset(stream_t *s)
{
    stream_sys_t *sys = s->p_sys;

    block_BytestreamEmpty( &sys->cache );

    /* Do the prebuffering */
    AStreamPrebufferBlock(s);
}