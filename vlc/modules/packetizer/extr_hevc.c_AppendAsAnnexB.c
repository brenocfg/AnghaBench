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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void AppendAsAnnexB(const block_t *p_block,
                           uint8_t **pp_dst, size_t *pi_dst)
{
    if(SIZE_MAX - p_block->i_buffer < *pi_dst )
        return;

    size_t i_realloc = p_block->i_buffer + *pi_dst;
    uint8_t *p_realloc = realloc(*pp_dst, i_realloc);
    if(p_realloc)
    {
        memcpy(&p_realloc[*pi_dst], p_block->p_buffer, p_block->i_buffer);
        *pi_dst = i_realloc;
        *pp_dst = p_realloc;
    }
}