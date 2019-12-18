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
struct TYPE_3__ {int /*<<< orphan*/  num; } ;
typedef  int FT_ULong ;
typedef  TYPE_1__ FT_Hashkey ;

/* Variables and functions */

__attribute__((used)) static FT_ULong
  hash_num_lookup( FT_Hashkey*  key )
  {
    FT_ULong  num = (FT_ULong)key->num;
    FT_ULong  res;


    /* Mocklisp hash function. */
    res = num & 0xFF;
    res = ( res << 5 ) - res + ( ( num >>  8 ) & 0xFF );
    res = ( res << 5 ) - res + ( ( num >> 16 ) & 0xFF );
    res = ( res << 5 ) - res + ( ( num >> 24 ) & 0xFF );

    return res;
  }