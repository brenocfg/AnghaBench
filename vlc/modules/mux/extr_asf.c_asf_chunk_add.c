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
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bo_addle_u16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_addle_u32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void asf_chunk_add( bo_t *bo,
                           int i_type, int i_len, int i_flags, int i_seq )
{
    bo_addle_u16( bo, i_type );
    bo_addle_u16( bo, i_len + 8 );
    bo_addle_u32( bo, i_seq );
    bo_addle_u16( bo, i_flags );
    bo_addle_u16( bo, i_len + 8 );
}