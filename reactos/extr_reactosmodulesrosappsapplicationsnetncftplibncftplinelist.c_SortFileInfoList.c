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
struct TYPE_3__ {int sortKey; int sortOrder; int nFileInfos; int /*<<< orphan*/ * vec; } ;
typedef  int /*<<< orphan*/ * FileInfoVec ;
typedef  int /*<<< orphan*/  FileInfoPtr ;
typedef  TYPE_1__* FileInfoListPtr ;

/* Variables and functions */
 int /*<<< orphan*/  BreadthFirstCmp ; 
 int /*<<< orphan*/  NameCmp ; 
 int /*<<< orphan*/  ReverseNameCmp ; 
 int /*<<< orphan*/  ReverseSizeCmp ; 
 int /*<<< orphan*/  ReverseTimeCmp ; 
 int /*<<< orphan*/  SizeCmp ; 
 int /*<<< orphan*/  TimeCmp ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 

void
SortFileInfoList(FileInfoListPtr list, int sortKey, int sortOrder)
{
	FileInfoVec fiv;
	FileInfoPtr fip;
	int i, j, n, n2;

	fiv = list->vec;
	if (fiv == NULL)
		return;

	if (list->sortKey == sortKey) {
		if (list->sortOrder == sortOrder)
			return;		/* Already sorted they you want. */

		/* Reverse the sort. */
		n = list->nFileInfos;
		if (n > 1) {
			n2 = n / 2;
			for (i=0; i<n2; i++) {
				j = n - i - 1;
				fip = fiv[i];
				fiv[i] = fiv[j];
				fiv[j] = fip;
			}
		}

		list->sortOrder = sortOrder;
	} else if ((sortKey == 'n') && (sortOrder == 'a')) {
		qsort(fiv, (size_t) list->nFileInfos, sizeof(FileInfoPtr),
			NameCmp);
		list->sortKey = sortKey;
		list->sortOrder = sortOrder;
	} else if ((sortKey == 'n') && (sortOrder == 'd')) {
		qsort(fiv, (size_t) list->nFileInfos, sizeof(FileInfoPtr),
			ReverseNameCmp);
		list->sortKey = sortKey;
		list->sortOrder = sortOrder;
	} else if ((sortKey == 't') && (sortOrder == 'a')) {
		qsort(fiv, (size_t) list->nFileInfos, sizeof(FileInfoPtr),
			TimeCmp);
		list->sortKey = sortKey;
		list->sortOrder = sortOrder;
	} else if ((sortKey == 't') && (sortOrder == 'd')) {
		qsort(fiv, (size_t) list->nFileInfos, sizeof(FileInfoPtr),
			ReverseTimeCmp);
		list->sortKey = sortKey;
		list->sortOrder = sortOrder;
	} else if ((sortKey == 's') && (sortOrder == 'a')) {
		qsort(fiv, (size_t) list->nFileInfos, sizeof(FileInfoPtr),
			SizeCmp);
		list->sortKey = sortKey;
		list->sortOrder = sortOrder;
	} else if ((sortKey == 's') && (sortOrder == 'd')) {
		qsort(fiv, (size_t) list->nFileInfos, sizeof(FileInfoPtr),
			ReverseSizeCmp);
		list->sortKey = sortKey;
		list->sortOrder = sortOrder;
	} else if (sortKey == 'b') {
		/* This is different from the rest. */
		list->sortKey = sortKey;
		list->sortOrder = sortOrder;
		qsort(fiv, (size_t) list->nFileInfos, sizeof(FileInfoPtr),
			BreadthFirstCmp);
	}
}