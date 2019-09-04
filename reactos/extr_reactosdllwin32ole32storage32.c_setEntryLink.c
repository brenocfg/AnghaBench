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
typedef  int ULONG ;
struct TYPE_3__ {void* dirRootEntry; void* rightChild; void* leftChild; } ;
typedef  void* DirRef ;
typedef  TYPE_1__ DirEntry ;

/* Variables and functions */
#define  DIRENTRY_RELATION_DIR 130 
#define  DIRENTRY_RELATION_NEXT 129 
#define  DIRENTRY_RELATION_PREVIOUS 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setEntryLink(DirEntry *entry, ULONG relation, DirRef new_target)
{
  switch (relation)
  {
    case DIRENTRY_RELATION_PREVIOUS:
      entry->leftChild = new_target;
      break;
    case DIRENTRY_RELATION_NEXT:
      entry->rightChild = new_target;
      break;
    case DIRENTRY_RELATION_DIR:
      entry->dirRootEntry = new_target;
      break;
    default:
      assert(0);
  }
}