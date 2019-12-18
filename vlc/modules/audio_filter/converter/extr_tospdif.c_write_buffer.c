#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_12__ {TYPE_1__* p_out_buf; } ;
typedef  TYPE_3__ filter_sys_t ;
struct TYPE_13__ {scalar_t__ i_length; int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_4__ block_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_big_endian (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  write_data (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_buffer( filter_t *p_filter, block_t *p_in_buf )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    write_data( p_filter, p_in_buf->p_buffer, p_in_buf->i_buffer,
                is_big_endian( p_filter, p_in_buf ) );
    p_sys->p_out_buf->i_length += p_in_buf->i_length;
}