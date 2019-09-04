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
struct TYPE_4__ {unsigned long num_bits; unsigned long buf_offset; unsigned long buf_size; scalar_t__ free_ent; scalar_t__ free_bits; scalar_t__ max_bits; unsigned long max_free; unsigned long* buf_tab; scalar_t__ buf_clear; } ;
typedef  unsigned long FT_UInt ;
typedef  TYPE_1__* FT_LzwState ;
typedef  int FT_Int32 ;
typedef  unsigned long FT_Int ;
typedef  unsigned long FT_Byte ;

/* Variables and functions */
 unsigned long LZW_INIT_BITS ; 
 unsigned long LZW_MASK (unsigned long) ; 
 unsigned long LZW_MAX_BITS ; 
 scalar_t__ ft_lzwstate_refill (TYPE_1__*) ; 

__attribute__((used)) static FT_Int32
  ft_lzwstate_get_code( FT_LzwState  state )
  {
    FT_UInt   num_bits = state->num_bits;
    FT_UInt   offset   = state->buf_offset;
    FT_Byte*  p;
    FT_Int    result;


    if ( state->buf_clear                    ||
         offset >= state->buf_size           ||
         state->free_ent >= state->free_bits )
    {
      if ( state->free_ent >= state->free_bits )
      {
        state->num_bits = ++num_bits;
        if ( num_bits > LZW_MAX_BITS )
          return -1;

        state->free_bits = state->num_bits < state->max_bits
                           ? (FT_UInt)( ( 1UL << num_bits ) - 256 )
                           : state->max_free + 1;
      }

      if ( state->buf_clear )
      {
        state->num_bits  = num_bits = LZW_INIT_BITS;
        state->free_bits = (FT_UInt)( ( 1UL << num_bits ) - 256 );
        state->buf_clear = 0;
      }

      if ( ft_lzwstate_refill( state ) < 0 )
        return -1;

      offset = 0;
    }

    state->buf_offset = offset + num_bits;

    p         = &state->buf_tab[offset >> 3];
    offset   &= 7;
    result    = *p++ >> offset;
    offset    = 8 - offset;
    num_bits -= offset;

    if ( num_bits >= 8 )
    {
      result   |= *p++ << offset;
      offset   += 8;
      num_bits -= 8;
    }
    if ( num_bits > 0 )
      result |= ( *p & LZW_MASK( num_bits ) ) << offset;

    return result;
  }