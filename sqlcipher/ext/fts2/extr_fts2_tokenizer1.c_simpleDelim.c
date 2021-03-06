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
struct TYPE_3__ {scalar_t__* delim; } ;
typedef  TYPE_1__ simple_tokenizer ;

/* Variables and functions */

__attribute__((used)) static int simpleDelim(simple_tokenizer *t, unsigned char c){
  return c<0x80 && t->delim[c];
}