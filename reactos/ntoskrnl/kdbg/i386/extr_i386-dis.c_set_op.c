#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int bfd_vma ;

/* Variables and functions */
 scalar_t__ mode_64bit ; 
 size_t op_ad ; 
 int* op_address ; 
 size_t* op_index ; 
 int* op_riprel ; 

__attribute__((used)) static void
set_op (bfd_vma op, int riprel)
{
  op_index[op_ad] = op_ad;
  if (mode_64bit)
    {
      op_address[op_ad] = op;
      op_riprel[op_ad] = riprel;
    }
  else
    {
      /* Mask to get a 32-bit address.  */
      op_address[op_ad] = op & 0xffffffff;
      op_riprel[op_ad] = riprel & 0xffffffff;
    }
}