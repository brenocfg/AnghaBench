#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct symbol {int dummy; } ;
struct TYPE_4__ {int count; TYPE_1__* tbl; } ;
struct TYPE_3__ {struct symbol* data; } ;

/* Variables and functions */
 TYPE_2__* x2a ; 

struct symbol *Symbol_Nth(int n)
{
  struct symbol *data;
  if( x2a && n>0 && n<=x2a->count ){
    data = x2a->tbl[n-1].data;
  }else{
    data = 0;
  }
  return data;
}