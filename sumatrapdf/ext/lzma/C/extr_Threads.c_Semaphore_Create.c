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
typedef  int /*<<< orphan*/  WRes ;
typedef  scalar_t__ UInt32 ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  CSemaphore ;

/* Variables and functions */
 int /*<<< orphan*/  CreateSemaphore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HandleToWRes (int /*<<< orphan*/ ) ; 

WRes Semaphore_Create(CSemaphore *p, UInt32 initCount, UInt32 maxCount)
{
  *p = CreateSemaphore(NULL, (LONG)initCount, (LONG)maxCount, NULL);
  return HandleToWRes(*p);
}