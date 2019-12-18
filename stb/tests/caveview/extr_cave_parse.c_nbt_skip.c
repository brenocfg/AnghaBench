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
struct TYPE_4__ {int* cur; } ;
typedef  TYPE_1__ nbt ;

/* Variables and functions */
 unsigned char TAG_End ; 
 int /*<<< orphan*/  nbt_skip_raw (TYPE_1__*,unsigned char) ; 

__attribute__((used)) static void nbt_skip(nbt *n)
{
   unsigned char type = *n->cur++;
   if (type == TAG_End)
      return;
   // skip name
   n->cur += (n->cur[0]*256 + n->cur[1]) + 2;
   nbt_skip_raw(n, type);
}