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
typedef  int stb_uint32 ;
struct TYPE_3__ {int (* hash ) (void*,int /*<<< orphan*/ ) ;int hash_size; int /*<<< orphan*/  population; int /*<<< orphan*/ * hash_table; int /*<<< orphan*/  hash_shift; } ;
typedef  TYPE_1__ stb_dupe ;

/* Variables and functions */
 int /*<<< orphan*/  stb_arr_push (int /*<<< orphan*/ ,void*) ; 
 int stub1 (void*,int /*<<< orphan*/ ) ; 

void stb_dupe_add(stb_dupe *sd, void *item)
{
   stb_uint32 hash = sd->hash(item, sd->hash_shift);
   int z = hash & (sd->hash_size-1);
   stb_arr_push(sd->hash_table[z], item);
   ++sd->population;
}