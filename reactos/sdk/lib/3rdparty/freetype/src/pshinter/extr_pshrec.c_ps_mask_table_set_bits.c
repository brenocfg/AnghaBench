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
struct TYPE_4__ {int num_bits; int* bytes; } ;
typedef  int /*<<< orphan*/  PS_Mask_Table ;
typedef  TYPE_1__* PS_Mask ;
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int FT_Int ;
typedef  scalar_t__ FT_Error ;
typedef  int FT_Byte ;

/* Variables and functions */
 scalar_t__ ps_mask_ensure (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ps_mask_table_last (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 

__attribute__((used)) static FT_Error
  ps_mask_table_set_bits( PS_Mask_Table   table,
                          const FT_Byte*  source,
                          FT_UInt         bit_pos,
                          FT_UInt         bit_count,
                          FT_Memory       memory )
  {
    FT_Error  error;
    PS_Mask   mask;


    error = ps_mask_table_last( table, memory, &mask );
    if ( error )
      goto Exit;

    error = ps_mask_ensure( mask, bit_count, memory );
    if ( error )
      goto Exit;

    mask->num_bits = bit_count;

    /* now, copy bits */
    {
      FT_Byte*  read  = (FT_Byte*)source + ( bit_pos >> 3 );
      FT_Int    rmask = 0x80 >> ( bit_pos & 7 );
      FT_Byte*  write = mask->bytes;
      FT_Int    wmask = 0x80;
      FT_Int    val;


      for ( ; bit_count > 0; bit_count-- )
      {
        val = write[0] & ~wmask;

        if ( read[0] & rmask )
          val |= wmask;

        write[0] = (FT_Byte)val;

        rmask >>= 1;
        if ( rmask == 0 )
        {
          read++;
          rmask = 0x80;
        }

        wmask >>= 1;
        if ( wmask == 0 )
        {
          write++;
          wmask = 0x80;
        }
      }
    }

  Exit:
    return error;
  }