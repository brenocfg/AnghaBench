#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  reverted; } ;
typedef  TYPE_1__ StorageBaseImpl ;

/* Variables and functions */
 int /*<<< orphan*/  StorageBaseImpl_DeleteAll (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void TransactedSharedImpl_Invalidate(StorageBaseImpl* This)
{
  if (!This->reverted)
  {
    TRACE("Storage invalidated (stg=%p)\n", This);

    This->reverted = TRUE;

    StorageBaseImpl_DeleteAll(This);
  }
}