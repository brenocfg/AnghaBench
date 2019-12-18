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
struct TYPE_3__ {int num_bits; int* bytes; } ;
typedef  TYPE_1__* PS_Mask ;
typedef  int FT_UInt ;
typedef  int FT_Byte ;

/* Variables and functions */

__attribute__((used)) static void
  ps_mask_clear_bit( PS_Mask  mask,
                     FT_UInt  idx )
  {
    FT_Byte*  p;


    if ( idx >= mask->num_bits )
      return;

    p    = mask->bytes + ( idx >> 3 );
    p[0] = (FT_Byte)( p[0] & ~( 0x80 >> ( idx & 7 ) ) );
  }