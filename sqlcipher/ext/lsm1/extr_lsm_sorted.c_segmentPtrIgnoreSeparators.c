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
struct TYPE_3__ {int flags; int nPtr; int /*<<< orphan*/ * aPtr; } ;
typedef  int /*<<< orphan*/  SegmentPtr ;
typedef  TYPE_1__ MultiCursor ;

/* Variables and functions */
 int CURSOR_READ_SEPARATORS ; 

__attribute__((used)) static int segmentPtrIgnoreSeparators(MultiCursor *pCsr, SegmentPtr *pPtr){
  return (pCsr->flags & CURSOR_READ_SEPARATORS)==0
      || (pPtr!=&pCsr->aPtr[pCsr->nPtr-1]);
}