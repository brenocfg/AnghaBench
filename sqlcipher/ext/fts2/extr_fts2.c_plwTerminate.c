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
struct TYPE_5__ {int iPos; TYPE_1__* dlw; } ;
struct TYPE_4__ {scalar_t__ iType; int /*<<< orphan*/  b; } ;
typedef  TYPE_2__ PLWriter ;

/* Variables and functions */
 scalar_t__ DL_DOCIDS ; 
 int /*<<< orphan*/  POS_END ; 
 int VARINT_MAX ; 
 int /*<<< orphan*/  dataBufferAppend (int /*<<< orphan*/ ,char*,int) ; 
 int putVarint (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void plwTerminate(PLWriter *pWriter){
  if( pWriter->dlw->iType>DL_DOCIDS ){
    char c[VARINT_MAX];
    int n = putVarint(c, POS_END);
    dataBufferAppend(pWriter->dlw->b, c, n);
  }
#ifndef NDEBUG
  /* Mark as terminated for assert in plwAdd(). */
  pWriter->iPos = -1;
#endif
}