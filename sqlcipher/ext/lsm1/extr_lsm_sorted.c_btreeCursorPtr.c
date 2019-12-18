#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int pageGetNRec (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pageGetPtr (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pageGetRecordPtr (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int btreeCursorPtr(u8 *aData, int nData, int iCell){
  int nCell;

  nCell = pageGetNRec(aData, nData);
  if( iCell>=nCell ){
    return (int)pageGetPtr(aData, nData);
  }
  return (int)pageGetRecordPtr(aData, nData, iCell);
}