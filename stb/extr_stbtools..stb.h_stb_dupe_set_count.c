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
struct TYPE_3__ {int /*<<< orphan*/ * dupes; int /*<<< orphan*/ * hash_table; } ;
typedef  TYPE_1__ stb_dupe ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int stb_arr_len (int /*<<< orphan*/ ) ; 

int stb_dupe_set_count(stb_dupe *sd, int num)
{
   assert(sd->hash_table == NULL);
   return stb_arr_len(sd->dupes[num]);
}