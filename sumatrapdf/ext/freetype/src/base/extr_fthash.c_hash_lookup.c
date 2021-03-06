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
struct TYPE_3__ {size_t data; } ;
typedef  TYPE_1__* FT_Hashnode ;
typedef  int /*<<< orphan*/  FT_Hashkey ;
typedef  int /*<<< orphan*/  FT_Hash ;

/* Variables and functions */
 TYPE_1__** hash_bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t*
  hash_lookup( FT_Hashkey  key,
               FT_Hash     hash )
  {
    FT_Hashnode*  np = hash_bucket( key, hash );


    return (*np) ? &(*np)->data
                 : NULL;
  }