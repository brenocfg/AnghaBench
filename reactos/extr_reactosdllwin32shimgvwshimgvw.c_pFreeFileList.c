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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {struct TYPE_6__* Next; TYPE_1__* Prev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * Next; } ;
typedef  TYPE_2__ SHIMGVW_FILENODE ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static VOID
pFreeFileList(SHIMGVW_FILENODE *root)
{
    SHIMGVW_FILENODE *conductor;

    root->Prev->Next = NULL;
    root->Prev = NULL;

    while (root)
    {
        conductor = root;
        root = conductor->Next;
        free(conductor);
    }
}