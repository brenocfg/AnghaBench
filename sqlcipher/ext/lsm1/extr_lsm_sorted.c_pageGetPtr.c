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
typedef  int /*<<< orphan*/  LsmPgno ;

/* Variables and functions */
 size_t SEGMENT_POINTER_OFFSET (int) ; 
 int /*<<< orphan*/  lsmGetU64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LsmPgno pageGetPtr(u8 *aData, int nData){
  return (LsmPgno)lsmGetU64(&aData[SEGMENT_POINTER_OFFSET(nData)]);
}