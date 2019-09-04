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
struct TYPE_4__ {int num_bits; int code_buffer; } ;
typedef  TYPE_1__ zbuf ;

/* Variables and functions */
 int /*<<< orphan*/  fill_bits (TYPE_1__*) ; 

__attribute__((used)) static unsigned int zreceive(zbuf *z, int n)
{
   unsigned int k;
   if (z->num_bits < n) fill_bits(z);
   k = z->code_buffer & ((1 << n) - 1);
   z->code_buffer >>= n;
   z->num_bits -= n;
   return k;   
}