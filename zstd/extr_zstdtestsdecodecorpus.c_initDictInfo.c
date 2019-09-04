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
typedef  int /*<<< orphan*/  dictOp ;
struct TYPE_4__ {int useDict; size_t dictContentSize; int /*<<< orphan*/  dictID; int /*<<< orphan*/ * dictContent; } ;
typedef  TYPE_1__ dictInfo ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static dictInfo initDictInfo(int useDict, size_t dictContentSize, BYTE* dictContent, U32 dictID){
    /* allocate space statically */
    dictInfo dictOp;
    memset(&dictOp, 0, sizeof(dictOp));
    dictOp.useDict = useDict;
    dictOp.dictContentSize = dictContentSize;
    dictOp.dictContent = dictContent;
    dictOp.dictID = dictID;
    return dictOp;
}