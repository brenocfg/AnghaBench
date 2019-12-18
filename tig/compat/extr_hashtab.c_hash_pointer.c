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
typedef  unsigned int hashval_t ;
typedef  scalar_t__ PTR ;

/* Variables and functions */
 int CHAR_BIT ; 
 int /*<<< orphan*/  mix (unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static hashval_t
hash_pointer (const PTR p)
{
  intptr_t v = (intptr_t) p;
  unsigned a, b, c;

  a = b = 0x9e3779b9;
  a += v >> (sizeof (intptr_t) * CHAR_BIT / 2);
  b += v & (((intptr_t) 1 << (sizeof (intptr_t) * CHAR_BIT / 2)) - 1);
  c = 0x42135234;
  mix (a, b, c);
  return c;
}