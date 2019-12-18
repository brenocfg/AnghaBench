#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ OrderFall; scalar_t__ MaxContext; scalar_t__ MinContext; int /*<<< orphan*/ * UnitsStart; int /*<<< orphan*/  FoundState; } ;
typedef  scalar_t__ CTX_PTR ;
typedef  TYPE_1__ CPpmd8 ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ CTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUCCESSOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateModel (TYPE_1__*) ; 

__attribute__((used)) static void NextContext(CPpmd8 *p)
{
  CTX_PTR c = CTX(SUCCESSOR(p->FoundState));
  if (p->OrderFall == 0 && (Byte *)c >= p->UnitsStart)
    p->MinContext = p->MaxContext = c;
  else
  {
    UpdateModel(p);
    p->MinContext = p->MaxContext;
  }
}