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
struct TYPE_3__ {scalar_t__ num_bits; int buf_size; scalar_t__ buf_offset; int /*<<< orphan*/  in_eof; int /*<<< orphan*/  buf_total; int /*<<< orphan*/  buf_tab; int /*<<< orphan*/  source; } ;
typedef  scalar_t__ FT_ULong ;
typedef  int FT_UInt ;
typedef  TYPE_1__* FT_LzwState ;

/* Variables and functions */
 int /*<<< orphan*/  FT_BOOL (int) ; 
 scalar_t__ FT_Stream_TryRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
  ft_lzwstate_refill( FT_LzwState  state )
  {
    FT_ULong  count;


    if ( state->in_eof )
      return -1;

    count = FT_Stream_TryRead( state->source,
                               state->buf_tab,
                               state->num_bits );  /* WHY? */

    state->buf_size   = (FT_UInt)count;
    state->buf_total += count;
    state->in_eof     = FT_BOOL( count < state->num_bits );
    state->buf_offset = 0;

    state->buf_size <<= 3;
    if ( state->buf_size > state->num_bits )
      state->buf_size -= state->num_bits - 1;
    else
      return -1; /* not enough data */

    if ( count == 0 )  /* end of file */
      return -1;

    return 0;
  }