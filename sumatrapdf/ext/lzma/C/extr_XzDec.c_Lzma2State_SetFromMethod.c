#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  Code; int /*<<< orphan*/  Init; int /*<<< orphan*/  SetProps; int /*<<< orphan*/  Free; int /*<<< orphan*/ * p; } ;
struct TYPE_6__ {int /*<<< orphan*/ * (* Alloc ) (TYPE_1__*,int) ;} ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ ISzAlloc ;
typedef  TYPE_2__ IStateCoder ;
typedef  int /*<<< orphan*/  CLzma2Dec ;

/* Variables and functions */
 int /*<<< orphan*/  Lzma2Dec_Construct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lzma2State_Code ; 
 int /*<<< orphan*/  Lzma2State_Free ; 
 int /*<<< orphan*/  Lzma2State_Init ; 
 int /*<<< orphan*/  Lzma2State_SetProps ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static SRes Lzma2State_SetFromMethod(IStateCoder *p, ISzAlloc *alloc)
{
  CLzma2Dec *decoder = alloc->Alloc(alloc, sizeof(CLzma2Dec));
  p->p = decoder;
  if (decoder == 0)
    return SZ_ERROR_MEM;
  p->Free = Lzma2State_Free;
  p->SetProps = Lzma2State_SetProps;
  p->Init = Lzma2State_Init;
  p->Code = Lzma2State_Code;
  Lzma2Dec_Construct(decoder);
  return SZ_OK;
}