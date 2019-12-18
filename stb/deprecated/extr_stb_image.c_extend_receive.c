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
struct TYPE_4__ {int code_bits; unsigned int code_buffer; } ;
typedef  TYPE_1__ jpeg ;

/* Variables and functions */
 unsigned int* bmask ; 
 int /*<<< orphan*/  grow_buffer_unsafe (TYPE_1__*) ; 
 unsigned int stbi_lrot (unsigned int,int) ; 

__attribute__((used)) static int extend_receive(jpeg *j, int n)
{
   unsigned int m = 1 << (n-1);
   unsigned int k;
   if (j->code_bits < n) grow_buffer_unsafe(j);

   #if 1
   k = stbi_lrot(j->code_buffer, n);
   j->code_buffer = k & ~bmask[n];
   k &= bmask[n];
   j->code_bits -= n;
   #else
   k = (j->code_buffer >> (32 - n)) & bmask[n];
   j->code_bits -= n;
   j->code_buffer <<= n;
   #endif
   // the following test is probably a random branch that won't
   // predict well. I tried to table accelerate it but failed.
   // maybe it's compiling as a conditional move?
   if (k < m)
      return (-1 << n) + k + 1;
   else
      return k;
}