#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  p; int /*<<< orphan*/  (* Init ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* SetProps ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ;} ;
struct TYPE_12__ {scalar_t__ (* Alloc ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {TYPE_8__ StateCoder; scalar_t__ srcWasFinished; scalar_t__ endPos; scalar_t__ curPos; scalar_t__ buf; } ;
struct TYPE_10__ {int /*<<< orphan*/  propsSize; int /*<<< orphan*/  props; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CXzFilter ;
typedef  TYPE_2__ CSeqInFilter ;

/* Variables and functions */
 int /*<<< orphan*/  BraState_SetFromMethod (TYPE_8__*,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  FILTER_BUF_SIZE ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_3__ g_Alloc ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static SRes SeqInFilter_Init(CSeqInFilter *p, const CXzFilter *props)
{
  if (!p->buf)
  {
    p->buf = g_Alloc.Alloc(&g_Alloc, FILTER_BUF_SIZE);
    if (!p->buf)
      return SZ_ERROR_MEM;
  }
  p->curPos = p->endPos = 0;
  p->srcWasFinished = 0;
  RINOK(BraState_SetFromMethod(&p->StateCoder, props->id, 1, &g_Alloc));
  RINOK(p->StateCoder.SetProps(p->StateCoder.p, props->props, props->propsSize, &g_Alloc));
  p->StateCoder.Init(p->StateCoder.p);
  return S_OK;
}