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
typedef  int uint32_t ;
struct TYPE_9__ {struct TYPE_9__* p_next; scalar_t__ p_data; scalar_t__ b_syntax_indicator; scalar_t__ p_payload_end; } ;
typedef  TYPE_1__ dvbpsi_psi_section_t ;
struct TYPE_10__ {int i_buffer; scalar_t__* p_buffer; scalar_t__ i_length; scalar_t__ i_dts; scalar_t__ i_pts; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 TYPE_2__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_ChainAppend (TYPE_2__**,TYPE_2__*) ; 
 int /*<<< orphan*/  block_ChainRelease (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 

block_t *WritePSISection( dvbpsi_psi_section_t* p_section )
{
    block_t   *p_psi, *p_first = NULL;

    while( p_section )
    {
        int i_size = (uint32_t)(p_section->p_payload_end - p_section->p_data) +
                  (p_section->b_syntax_indicator ? 4 : 0);

        p_psi = block_Alloc( i_size + 1 );
        if( !p_psi )
            goto error;
        p_psi->i_pts = 0;
        p_psi->i_dts = 0;
        p_psi->i_length = 0;
        p_psi->i_buffer = i_size + 1;

        p_psi->p_buffer[0] = 0; /* pointer */
        memcpy( p_psi->p_buffer + 1,
                p_section->p_data,
                i_size );

        block_ChainAppend( &p_first, p_psi );

        p_section = p_section->p_next;
    }

    return( p_first );

error:
    if( p_first )
        block_ChainRelease( p_first );
    return NULL;
}