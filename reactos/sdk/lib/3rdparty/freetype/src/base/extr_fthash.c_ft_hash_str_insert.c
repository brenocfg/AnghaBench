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
struct TYPE_3__ {char const* str; } ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  TYPE_1__ FT_Hashkey ;
typedef  int /*<<< orphan*/  FT_Hash ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  hash_insert (TYPE_1__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

FT_Error
  ft_hash_str_insert( const char*  key,
                      size_t       data,
                      FT_Hash      hash,
                      FT_Memory    memory )
  {
    FT_Hashkey  hk;


    hk.str = key;

    return hash_insert( hk, data, hash, memory );
  }