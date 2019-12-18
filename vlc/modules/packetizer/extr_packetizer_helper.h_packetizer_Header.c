#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {scalar_t__ i_offset; int /*<<< orphan*/  bytestream; int /*<<< orphan*/  i_state; } ;
typedef  TYPE_1__ packetizer_t ;
struct TYPE_10__ {int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_NOSYNC ; 
 TYPE_2__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_BytestreamEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 TYPE_2__* packetizer_Packetize (TYPE_1__*,TYPE_2__**) ; 

__attribute__((used)) static inline void packetizer_Header( packetizer_t *p_pack,
                                      const uint8_t *p_header, int i_header )
{
    block_t *p_init = block_Alloc( i_header );
    if( !p_init )
        return;

    memcpy( p_init->p_buffer, p_header, i_header );

    block_t *p_pic;
    while( ( p_pic = packetizer_Packetize( p_pack, &p_init ) ) )
        block_Release( p_pic ); /* Should not happen (only sequence header) */
    while( ( p_pic = packetizer_Packetize( p_pack, NULL ) ) )
        block_Release( p_pic );

    p_pack->i_state = STATE_NOSYNC;
    block_BytestreamEmpty( &p_pack->bytestream );
    p_pack->i_offset = 0;
}