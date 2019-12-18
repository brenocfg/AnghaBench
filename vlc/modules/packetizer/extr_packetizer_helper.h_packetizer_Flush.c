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
struct TYPE_3__ {int /*<<< orphan*/  p_private; int /*<<< orphan*/  (* pf_reset ) (int /*<<< orphan*/ ,int) ;scalar_t__ i_offset; int /*<<< orphan*/  bytestream; int /*<<< orphan*/  i_state; } ;
typedef  TYPE_1__ packetizer_t ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_NOSYNC ; 
 int /*<<< orphan*/  block_BytestreamEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void packetizer_Flush( packetizer_t *p_pack )
{
    p_pack->i_state = STATE_NOSYNC;
    block_BytestreamEmpty( &p_pack->bytestream );
    p_pack->i_offset = 0;
    p_pack->pf_reset( p_pack->p_private, true );
}