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
struct TYPE_4__ {scalar_t__ num_masks; scalar_t__ masks; } ;
typedef  TYPE_1__* PS_Mask_Table ;
typedef  scalar_t__ PS_Mask ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 scalar_t__ FT_Err_Ok ; 
 scalar_t__ ps_mask_table_alloc (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static FT_Error
  ps_mask_table_last( PS_Mask_Table  table,
                      FT_Memory      memory,
                      PS_Mask       *amask )
  {
    FT_Error  error = FT_Err_Ok;
    FT_UInt   count;
    PS_Mask   mask;


    count = table->num_masks;
    if ( count == 0 )
    {
      error = ps_mask_table_alloc( table, memory, &mask );
      if ( error )
        goto Exit;
    }
    else
      mask = table->masks + count - 1;

  Exit:
    *amask = mask;
    return error;
  }