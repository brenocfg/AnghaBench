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
struct TYPE_3__ {int max_bits; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_1__* PS_Mask ;
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 int FT_PAD_CEIL (int,int) ; 
 int /*<<< orphan*/  FT_RENEW_ARRAY (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static FT_Error
  ps_mask_ensure( PS_Mask    mask,
                  FT_UInt    count,
                  FT_Memory  memory )
  {
    FT_UInt   old_max = ( mask->max_bits + 7 ) >> 3;
    FT_UInt   new_max = ( count          + 7 ) >> 3;
    FT_Error  error   = FT_Err_Ok;


    if ( new_max > old_max )
    {
      new_max = FT_PAD_CEIL( new_max, 8 );
      if ( !FT_RENEW_ARRAY( mask->bytes, old_max, new_max ) )
        mask->max_bits = new_max * 8;
    }
    return error;
  }