#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ num_masks; int /*<<< orphan*/  masks; } ;
struct TYPE_4__ {TYPE_2__ counters; } ;
typedef  int /*<<< orphan*/  PS_Mask ;
typedef  TYPE_1__* PS_Dimension ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  scalar_t__ FT_Int ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 scalar_t__ FT_Err_Ok ; 
 scalar_t__ ps_mask_set_bit (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ps_mask_table_alloc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ps_mask_test_bit (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static FT_Error
  ps_dimension_add_counter( PS_Dimension  dim,
                            FT_Int        hint1,
                            FT_Int        hint2,
                            FT_Int        hint3,
                            FT_Memory     memory )
  {
    FT_Error  error   = FT_Err_Ok;
    FT_UInt   count   = dim->counters.num_masks;
    PS_Mask   counter = dim->counters.masks;


    /* try to find an existing counter mask that already uses */
    /* one of these stems here                                */
    for ( ; count > 0; count--, counter++ )
    {
      if ( ps_mask_test_bit( counter, hint1 ) ||
           ps_mask_test_bit( counter, hint2 ) ||
           ps_mask_test_bit( counter, hint3 ) )
        break;
    }

    /* create a new counter when needed */
    if ( count == 0 )
    {
      error = ps_mask_table_alloc( &dim->counters, memory, &counter );
      if ( error )
        goto Exit;
    }

    /* now, set the bits for our hints in the counter mask */
    if ( hint1 >= 0 )
    {
      error = ps_mask_set_bit( counter, (FT_UInt)hint1, memory );
      if ( error )
        goto Exit;
    }

    if ( hint2 >= 0 )
    {
      error = ps_mask_set_bit( counter, (FT_UInt)hint2, memory );
      if ( error )
        goto Exit;
    }

    if ( hint3 >= 0 )
    {
      error = ps_mask_set_bit( counter, (FT_UInt)hint3, memory );
      if ( error )
        goto Exit;
    }

  Exit:
    return error;
  }