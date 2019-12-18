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
typedef  scalar_t__ sqlite_int64 ;
struct TYPE_6__ {int has_iPrevDocid; scalar_t__ iPrevDocid; int /*<<< orphan*/  b; } ;
struct TYPE_5__ {scalar_t__ iOffset; scalar_t__ iPos; scalar_t__ iColumn; TYPE_2__* dlw; } ;
typedef  TYPE_1__ PLWriter ;
typedef  TYPE_2__ DLWriter ;

/* Variables and functions */
 int VARINT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferAppend (int /*<<< orphan*/ ,char*,int) ; 
 int putVarint (char*,scalar_t__) ; 

__attribute__((used)) static void plwInit(PLWriter *pWriter, DLWriter *dlw, sqlite_int64 iDocid){
  char c[VARINT_MAX];
  int n;

  pWriter->dlw = dlw;

  /* Docids must ascend. */
  assert( !pWriter->dlw->has_iPrevDocid || iDocid>pWriter->dlw->iPrevDocid );
  n = putVarint(c, iDocid-pWriter->dlw->iPrevDocid);
  dataBufferAppend(pWriter->dlw->b, c, n);
  pWriter->dlw->iPrevDocid = iDocid;
#ifndef NDEBUG
  pWriter->dlw->has_iPrevDocid = 1;
#endif

  pWriter->iColumn = 0;
  pWriter->iPos = 0;
  pWriter->iOffset = 0;
}