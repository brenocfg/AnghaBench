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
typedef  size_t ssize_t ;
struct TYPE_3__ {size_t i_size; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */

__attribute__((used)) static bool block_WillRealloc( block_t *p_block, ssize_t i_prebody, size_t i_body )
{
    if( i_prebody <= 0 && i_body <= (size_t)(-i_prebody) )
        return false;
    else
        return ( i_prebody + i_body <= p_block->i_size );
}