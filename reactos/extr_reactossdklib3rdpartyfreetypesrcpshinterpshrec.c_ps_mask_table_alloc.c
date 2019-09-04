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
struct TYPE_7__ {scalar_t__ end_point; scalar_t__ num_bits; } ;
struct TYPE_6__ {scalar_t__ num_masks; scalar_t__ max_masks; scalar_t__ masks; } ;
typedef  TYPE_1__* PS_Mask_Table ;
typedef  TYPE_2__* PS_Mask ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 scalar_t__ FT_Err_Ok ; 
 scalar_t__ ps_mask_table_ensure (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  ps_mask_table_alloc( PS_Mask_Table  table,
                       FT_Memory      memory,
                       PS_Mask       *amask )
  {
    FT_UInt   count;
    FT_Error  error = FT_Err_Ok;
    PS_Mask   mask  = NULL;


    count = table->num_masks;
    count++;

    if ( count > table->max_masks )
    {
      error = ps_mask_table_ensure( table, count, memory );
      if ( error )
        goto Exit;
    }

    mask             = table->masks + count - 1;
    mask->num_bits   = 0;
    mask->end_point  = 0;
    table->num_masks = count;

  Exit:
    *amask = mask;
    return error;
  }