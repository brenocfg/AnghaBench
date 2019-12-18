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
struct TYPE_4__ {int alloced; } ;
typedef  TYPE_1__ stb_idict ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stb_idict_init (TYPE_1__*,unsigned int) ; 

stb_idict * stb_idict_new_size(unsigned int size)
{
   stb_idict *e = (stb_idict *) malloc(sizeof(*e));
   if (e) {
      // round up to power of 2
      while ((size & (size-1)) != 0) // while more than 1 bit is set
         size += (size & ~(size-1)); // add the lowest set bit
      stb_idict_init(e, size);
      e->alloced = 1;
   }
   return e;
}