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
struct TYPE_3__ {int* NS2BSIndx; void** NS2Indx; void** Indx2Units; void** Units2Indx; scalar_t__ Base; } ;
typedef  TYPE_1__ CPpmd8 ;
typedef  void* Byte ;

/* Variables and functions */
 unsigned int PPMD_NUM_INDEXES ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

void Ppmd8_Construct(CPpmd8 *p)
{
  unsigned i, k, m;

  p->Base = 0;

  for (i = 0, k = 0; i < PPMD_NUM_INDEXES; i++)
  {
    unsigned step = (i >= 12 ? 4 : (i >> 2) + 1);
    do { p->Units2Indx[k++] = (Byte)i; } while(--step);
    p->Indx2Units[i] = (Byte)k;
  }

  p->NS2BSIndx[0] = (0 << 1);
  p->NS2BSIndx[1] = (1 << 1);
  memset(p->NS2BSIndx + 2, (2 << 1), 9);
  memset(p->NS2BSIndx + 11, (3 << 1), 256 - 11);

  for (i = 0; i < 5; i++)
    p->NS2Indx[i] = (Byte)i;
  for (m = i, k = 1; i < 260; i++)
  {
    p->NS2Indx[i] = (Byte)m;
    if (--k == 0)
      k = (++m) - 4;
  }
}