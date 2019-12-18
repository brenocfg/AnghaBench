#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  count ;
typedef  scalar_t__ UInt32 ;
struct TYPE_6__ {scalar_t__ LoUnit; scalar_t__ HiUnit; int /*<<< orphan*/ * Stamps; int /*<<< orphan*/ * FreeList; int /*<<< orphan*/ * UnitsStart; } ;
struct TYPE_5__ {scalar_t__ Stamp; int /*<<< orphan*/  Next; int /*<<< orphan*/  NU; } ;
typedef  int /*<<< orphan*/  CPpmd8_Node_Ref ;
typedef  TYPE_1__ CPpmd8_Node ;
typedef  TYPE_2__ CPpmd8 ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ EMPTY_NODE ; 
 TYPE_1__* NODE (int /*<<< orphan*/ ) ; 
 int PPMD_NUM_INDEXES ; 
 size_t U2I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ExpandTextArea(CPpmd8 *p)
{
  UInt32 count[PPMD_NUM_INDEXES];
  unsigned i;
  memset(count, 0, sizeof(count));
  if (p->LoUnit != p->HiUnit)
    ((CPpmd8_Node *)p->LoUnit)->Stamp = 0;
  
  {
    CPpmd8_Node *node = (CPpmd8_Node *)p->UnitsStart;
    for (; node->Stamp == EMPTY_NODE; node += node->NU)
    {
      node->Stamp = 0;
      count[U2I(node->NU)]++;
    }
    p->UnitsStart = (Byte *)node;
  }
  
  for (i = 0; i < PPMD_NUM_INDEXES; i++)
  {
    CPpmd8_Node_Ref *next = (CPpmd8_Node_Ref *)&p->FreeList[i];
    while (count[i] != 0)
    {
      CPpmd8_Node *node = NODE(*next);
      while (node->Stamp == 0)
      {
        *next = node->Next;
        node = NODE(*next);
        p->Stamps[i]--;
        if (--count[i] == 0)
          break;
      }
      next = &node->Next;
    }
  }
}