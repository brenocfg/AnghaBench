#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__** vec; TYPE_1__* first; scalar_t__ nFileInfos; } ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__** FileInfoVec ;
typedef  TYPE_1__* FileInfoPtr ;
typedef  TYPE_3__* FileInfoListPtr ;

/* Variables and functions */
 scalar_t__ calloc (size_t,int) ; 

void
VectorizeFileInfoList(FileInfoListPtr list)
{
	FileInfoVec fiv;
	FileInfoPtr fip;
	int i;

	fiv = (FileInfoVec) calloc((size_t) (list->nFileInfos + 1), sizeof(FileInfoPtr));
	if (fiv != (FileInfoVec) 0) {
		for (i = 0, fip = list->first; fip != NULL; fip = fip->next, i++)
			fiv[i] = fip;
		list->vec = fiv;
	}
}