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
struct TYPE_4__ {int /*<<< orphan*/  db; int /*<<< orphan*/  FileNames; int /*<<< orphan*/  FileNameOffsets; int /*<<< orphan*/  FileIndexToFolderIndexMap; int /*<<< orphan*/  FolderStartFileIndex; int /*<<< orphan*/  PackStreamStartPositions; int /*<<< orphan*/  FolderStartPackStreamIndex; } ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  TYPE_1__ CSzArEx ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAlloc_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SzArEx_Init (TYPE_1__*) ; 
 int /*<<< orphan*/  SzAr_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void SzArEx_Free(CSzArEx *p, ISzAlloc *alloc)
{
  IAlloc_Free(alloc, p->FolderStartPackStreamIndex);
  IAlloc_Free(alloc, p->PackStreamStartPositions);
  IAlloc_Free(alloc, p->FolderStartFileIndex);
  IAlloc_Free(alloc, p->FileIndexToFolderIndexMap);

  IAlloc_Free(alloc, p->FileNameOffsets);
  Buf_Free(&p->FileNames, alloc);

  SzAr_Free(&p->db, alloc);
  SzArEx_Init(p);
}