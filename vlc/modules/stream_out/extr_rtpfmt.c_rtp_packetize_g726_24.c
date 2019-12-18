#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sout_stream_id_sys_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int rtp_packetize_g726 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rtp_packetize_g726_24( sout_stream_id_sys_t *id, block_t *in )
{
    return rtp_packetize_g726( id, in, 8 );
}