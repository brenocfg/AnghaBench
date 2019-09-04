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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  ownerDirEntry; int /*<<< orphan*/ * headOfStreamPlaceHolder; int /*<<< orphan*/ * parentStorage; } ;
typedef  int /*<<< orphan*/  StorageImpl ;
typedef  TYPE_1__ SmallBlockChainStream ;
typedef  int /*<<< orphan*/  DirRef ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

SmallBlockChainStream* SmallBlockChainStream_Construct(
  StorageImpl* parentStorage,
  ULONG*         headOfStreamPlaceHolder,
  DirRef         dirEntry)
{
  SmallBlockChainStream* newStream;

  newStream = HeapAlloc(GetProcessHeap(), 0, sizeof(SmallBlockChainStream));

  newStream->parentStorage      = parentStorage;
  newStream->headOfStreamPlaceHolder = headOfStreamPlaceHolder;
  newStream->ownerDirEntry      = dirEntry;

  return newStream;
}