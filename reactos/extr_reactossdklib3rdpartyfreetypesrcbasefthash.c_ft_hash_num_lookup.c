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
typedef  int /*<<< orphan*/  FT_Int ;
typedef  TYPE_1__ FT_Hashkey ;
typedef  int /*<<< orphan*/  FT_Hash ;

/* Variables and functions */
 size_t* hash_lookup (TYPE_1__,int /*<<< orphan*/ ) ; 

size_t*
  ft_hash_num_lookup( FT_Int   num,
                      FT_Hash  hash )
  {
    FT_Hashkey  hk;


    hk.num = num;

    return hash_lookup( hk, hash );
  }