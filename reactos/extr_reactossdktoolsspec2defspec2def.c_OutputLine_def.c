#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct TYPE_7__ {int uFlags; int nOrdinal; scalar_t__ nCallingConvention; TYPE_1__ strName; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ EXPORT ;

/* Variables and functions */
 scalar_t__ CC_EXTERN ; 
 int /*<<< orphan*/  DbgPrint (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FL_NONAME ; 
 int FL_ORDINAL ; 
 int FL_PRIVATE ; 
 int /*<<< orphan*/  OutputLine_def_GCC (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  OutputLine_def_MS (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ gbMSComp ; 

int
OutputLine_def(FILE *fileDest, EXPORT *pexp)
{
    DbgPrint("OutputLine_def: '%.*s'...\n", pexp->strName.len, pexp->strName.buf);
    fprintf(fileDest, " ");

    if (gbMSComp)
        OutputLine_def_MS(fileDest, pexp);
    else
        OutputLine_def_GCC(fileDest, pexp);

    if (pexp->uFlags & FL_ORDINAL)
    {
        fprintf(fileDest, " @%d", pexp->nOrdinal);
    }

    if (pexp->uFlags & FL_NONAME)
    {
        fprintf(fileDest, " NONAME");
    }

    /* Either PRIVATE or DATA */
    if (pexp->uFlags & FL_PRIVATE)
    {
        fprintf(fileDest, " PRIVATE");
    }
    else if (pexp->nCallingConvention == CC_EXTERN)
    {
        fprintf(fileDest, " DATA");
    }

    fprintf(fileDest, "\n");

    return 1;
}