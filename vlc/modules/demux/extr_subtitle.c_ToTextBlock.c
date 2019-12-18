#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  psz_text; } ;
typedef  TYPE_1__ subtitle_t ;
struct TYPE_7__ {int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 TYPE_2__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *ToTextBlock( const subtitle_t *p_subtitle )
{
    block_t *p_block;
    size_t i_len = strlen( p_subtitle->psz_text ) + 1;

    if( i_len <= 1 || !(p_block = block_Alloc( i_len )) )
        return NULL;

    memcpy( p_block->p_buffer, p_subtitle->psz_text, i_len );

    return p_block;
}