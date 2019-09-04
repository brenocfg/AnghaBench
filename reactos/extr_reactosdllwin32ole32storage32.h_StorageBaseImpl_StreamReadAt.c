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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  ULARGE_INTEGER ;
struct TYPE_6__ {TYPE_1__* baseVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* StreamReadAt ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ StorageBaseImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DirRef ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline HRESULT StorageBaseImpl_StreamReadAt(StorageBaseImpl *This,
  DirRef index, ULARGE_INTEGER offset, ULONG size, void *buffer, ULONG *bytesRead)
{
  return This->baseVtbl->StreamReadAt(This, index, offset, size, buffer, bytesRead);
}