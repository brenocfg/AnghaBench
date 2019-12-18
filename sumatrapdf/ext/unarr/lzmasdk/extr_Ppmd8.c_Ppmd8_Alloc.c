#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_9__ {int Size; int AlignOffset; int /*<<< orphan*/ * Base; } ;
struct TYPE_8__ {scalar_t__ (* Alloc ) (TYPE_1__*,int) ;} ;
typedef  TYPE_1__ ISzAlloc ;
typedef  TYPE_2__ CPpmd8 ;
typedef  int /*<<< orphan*/  Byte ;
typedef  int /*<<< orphan*/  Bool ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  Ppmd8_Free (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  True ; 
 scalar_t__ stub1 (TYPE_1__*,int) ; 

Bool Ppmd8_Alloc(CPpmd8 *p, UInt32 size, ISzAlloc *alloc)
{
  if (p->Base == 0 || p->Size != size)
  {
    Ppmd8_Free(p, alloc);
    p->AlignOffset =
      #ifdef PPMD_32BIT
        (4 - size) & 3;
      #else
        4 - (size & 3);
      #endif
    if ((p->Base = (Byte *)alloc->Alloc(alloc, p->AlignOffset + size)) == 0)
      return False;
    p->Size = size;
  }
  return True;
}