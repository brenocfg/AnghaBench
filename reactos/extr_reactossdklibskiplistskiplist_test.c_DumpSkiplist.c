#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* Distance; struct TYPE_4__** Next; scalar_t__ Element; } ;
struct TYPE_5__ {scalar_t__ MaximumLevel; TYPE_1__ Head; } ;
typedef  TYPE_1__* PSKIPLIST_NODE ;
typedef  TYPE_2__* PSKIPLIST ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
DumpSkiplist(PSKIPLIST Skiplist)
{
    CHAR i;
    DWORD j;
    PSKIPLIST_NODE pNode;

    printf("======= DUMPING SKIPLIST =======\n");

    for (i = Skiplist->MaximumLevel + 1; --i >= 0;)
    {
        pNode = &Skiplist->Head;
        printf("H");

        while (pNode->Next[i])
        {
            printf("-");

            // By using the Distance array for painting the lines, we verify both the links and the distances for correctness.
            for (j = 1; j < pNode->Distance[i]; j++)
                printf("---");

            printf("%02Iu", (DWORD_PTR)pNode->Next[i]->Element);

            pNode = pNode->Next[i];
        }

        printf("\n");
    }

    printf("================================\n\n");
}