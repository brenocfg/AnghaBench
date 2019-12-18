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
struct TYPE_3__ {int /*<<< orphan*/  bytestream; } ;
typedef  TYPE_1__ packetizer_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_BytestreamRelease (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void packetizer_Clean( packetizer_t *p_pack )
{
    block_BytestreamRelease( &p_pack->bytestream );
}