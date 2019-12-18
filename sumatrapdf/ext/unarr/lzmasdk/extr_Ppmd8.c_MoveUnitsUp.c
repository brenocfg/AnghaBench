#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* FreeList; int /*<<< orphan*/ * UnitsStart; } ;
typedef  TYPE_1__ CPpmd8 ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  I2U (unsigned int) ; 
 int /*<<< orphan*/  InsertNode (TYPE_1__*,void*,unsigned int) ; 
 int /*<<< orphan*/  MyMem12Cpy (void*,void*,unsigned int) ; 
 scalar_t__ REF (void*) ; 
 void* RemoveNode (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  U2B (int /*<<< orphan*/ ) ; 
 unsigned int U2I (unsigned int) ; 

__attribute__((used)) static void *MoveUnitsUp(CPpmd8 *p, void *oldPtr, unsigned nu)
{
  unsigned indx = U2I(nu);
  void *ptr;
  if ((Byte *)oldPtr > p->UnitsStart + 16 * 1024 || REF(oldPtr) > p->FreeList[indx])
    return oldPtr;
  ptr = RemoveNode(p, indx);
  MyMem12Cpy(ptr, oldPtr, nu);
  if ((Byte*)oldPtr != p->UnitsStart)
    InsertNode(p, oldPtr, indx);
  else
    p->UnitsStart += U2B(I2U(indx));
  return ptr;
}