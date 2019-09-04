#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ num_hints; TYPE_1__* hints; } ;
struct TYPE_7__ {int /*<<< orphan*/  masks; TYPE_3__ hints; } ;
struct TYPE_6__ {int pos; int len; scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  PS_Mask ;
typedef  TYPE_1__* PS_Hint ;
typedef  TYPE_2__* PS_Dimension ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int FT_Int ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 scalar_t__ PS_HINT_FLAG_BOTTOM ; 
 scalar_t__ PS_HINT_FLAG_GHOST ; 
 int /*<<< orphan*/  ps_hint_table_alloc (TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  ps_mask_set_bit (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_mask_table_last (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static FT_Error
  ps_dimension_add_t1stem( PS_Dimension  dim,
                           FT_Int        pos,
                           FT_Int        len,
                           FT_Memory     memory,
                           FT_Int       *aindex )
  {
    FT_Error  error = FT_Err_Ok;
    FT_UInt   flags = 0;


    /* detect ghost stem */
    if ( len < 0 )
    {
      flags |= PS_HINT_FLAG_GHOST;
      if ( len == -21 )
      {
        flags |= PS_HINT_FLAG_BOTTOM;
        pos   += len;
      }
      len = 0;
    }

    if ( aindex )
      *aindex = -1;

    /* now, lookup stem in the current hints table */
    {
      PS_Mask  mask;
      FT_UInt  idx;
      FT_UInt  max  = dim->hints.num_hints;
      PS_Hint  hint = dim->hints.hints;


      for ( idx = 0; idx < max; idx++, hint++ )
      {
        if ( hint->pos == pos && hint->len == len )
          break;
      }

      /* we need to create a new hint in the table */
      if ( idx >= max )
      {
        error = ps_hint_table_alloc( &dim->hints, memory, &hint );
        if ( error )
          goto Exit;

        hint->pos   = pos;
        hint->len   = len;
        hint->flags = flags;
      }

      /* now, store the hint in the current mask */
      error = ps_mask_table_last( &dim->masks, memory, &mask );
      if ( error )
        goto Exit;

      error = ps_mask_set_bit( mask, idx, memory );
      if ( error )
        goto Exit;

      if ( aindex )
        *aindex = (FT_Int)idx;
    }

  Exit:
    return error;
  }