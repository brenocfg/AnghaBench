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
struct TYPE_3__ {scalar_t__ num_bits; int* bytes; } ;
typedef  TYPE_1__* PS_Mask ;
typedef  scalar_t__ FT_UInt ;
typedef  int FT_Int ;

/* Variables and functions */

__attribute__((used)) static FT_Int
  ps_mask_test_bit( PS_Mask  mask,
                    FT_Int   idx )
  {
    if ( (FT_UInt)idx >= mask->num_bits )
      return 0;

    return mask->bytes[idx >> 3] & ( 0x80 >> ( idx & 7 ) );
  }