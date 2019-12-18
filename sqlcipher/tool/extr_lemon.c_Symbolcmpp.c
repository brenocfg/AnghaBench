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
struct symbol {scalar_t__ type; char* name; int index; } ;

/* Variables and functions */
 scalar_t__ MULTITERMINAL ; 

int Symbolcmpp(const void *_a, const void *_b)
{
  const struct symbol *a = *(const struct symbol **) _a;
  const struct symbol *b = *(const struct symbol **) _b;
  int i1 = a->type==MULTITERMINAL ? 3 : a->name[0]>'Z' ? 2 : 1;
  int i2 = b->type==MULTITERMINAL ? 3 : b->name[0]>'Z' ? 2 : 1;
  return i1==i2 ? a->index - b->index : i1 - i2;
}