#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int Range; int Code; TYPE_1__* Stream; } ;
struct TYPE_4__ {int (* Read ) (void*) ;} ;
typedef  TYPE_2__ CPpmd7z_RangeDec ;

/* Variables and functions */
 int kTopValue ; 
 int stub1 (void*) ; 
 int stub2 (void*) ; 

__attribute__((used)) static void Range_Normalize(CPpmd7z_RangeDec *p)
{
  if (p->Range < kTopValue)
  {
    p->Code = (p->Code << 8) | p->Stream->Read((void *)p->Stream);
    p->Range <<= 8;
    if (p->Range < kTopValue)
    {
      p->Code = (p->Code << 8) | p->Stream->Read((void *)p->Stream);
      p->Range <<= 8;
    }
  }
}