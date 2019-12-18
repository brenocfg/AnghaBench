#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  masks; } ;
typedef  TYPE_1__* PS_Dimension ;
typedef  int /*<<< orphan*/  FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  scalar_t__ FT_Error ;
typedef  int /*<<< orphan*/  FT_Byte ;

/* Variables and functions */
 scalar_t__ ps_dimension_reset_mask (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ps_mask_table_set_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  ps_dimension_set_mask_bits( PS_Dimension    dim,
                              const FT_Byte*  source,
                              FT_UInt         source_pos,
                              FT_UInt         source_bits,
                              FT_UInt         end_point,
                              FT_Memory       memory )
  {
    FT_Error  error;


    /* reset current mask, if any */
    error = ps_dimension_reset_mask( dim, end_point, memory );
    if ( error )
      goto Exit;

    /* set bits in new mask */
    error = ps_mask_table_set_bits( &dim->masks, source,
                                    source_pos, source_bits, memory );

  Exit:
    return error;
  }