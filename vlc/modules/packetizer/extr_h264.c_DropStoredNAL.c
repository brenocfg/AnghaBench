#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * p_head; int /*<<< orphan*/ ** pp_append; } ;
struct TYPE_6__ {int /*<<< orphan*/ * p_head; int /*<<< orphan*/ ** pp_append; } ;
struct TYPE_7__ {TYPE_1__ leading; TYPE_2__ frame; } ;
typedef  TYPE_3__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DropStoredNAL( decoder_sys_t *p_sys )
{
    block_ChainRelease( p_sys->frame.p_head );
    block_ChainRelease( p_sys->leading.p_head );
    p_sys->frame.p_head = NULL;
    p_sys->frame.pp_append = &p_sys->frame.p_head;
    p_sys->leading.p_head = NULL;
    p_sys->leading.pp_append = &p_sys->leading.p_head;
}