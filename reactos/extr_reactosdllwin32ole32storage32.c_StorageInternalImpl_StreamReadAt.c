#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  ULARGE_INTEGER ;
struct TYPE_2__ {int /*<<< orphan*/  parentStorage; } ;
typedef  TYPE_1__ StorageInternalImpl ;
typedef  int /*<<< orphan*/  StorageBaseImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DirRef ;

/* Variables and functions */
 int /*<<< orphan*/  StorageBaseImpl_StreamReadAt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT StorageInternalImpl_StreamReadAt(StorageBaseImpl *base,
  DirRef index, ULARGE_INTEGER offset, ULONG size, void *buffer, ULONG *bytesRead)
{
  StorageInternalImpl* This = (StorageInternalImpl*) base;

  return StorageBaseImpl_StreamReadAt(This->parentStorage,
    index, offset, size, buffer, bytesRead);
}