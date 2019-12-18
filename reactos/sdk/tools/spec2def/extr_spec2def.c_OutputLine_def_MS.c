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
struct TYPE_6__ {char* buf; char* len; } ;
struct TYPE_5__ {scalar_t__ nCallingConvention; int uFlags; int nNumber; TYPE_3__ strName; TYPE_3__ strTarget; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ EXPORT ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 scalar_t__ CC_FASTCALL ; 
 scalar_t__ CC_STDCALL ; 
 scalar_t__ CC_STUB ; 
 int FL_NORELAY ; 
 int FL_STUB ; 
 int /*<<< orphan*/  PrintName (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*,int) ; 
 scalar_t__ ScanToken (char*,char) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ gbImportLib ; 
 scalar_t__ gbTracing ; 
 scalar_t__ giArch ; 

void
OutputLine_def_MS(FILE *fileDest, EXPORT *pexp)
{
    PrintName(fileDest, pexp, &pexp->strName, 0);

    if (gbImportLib)
    {
        /* Redirect to a stub function, to get the right decoration in the lib */
        fprintf(fileDest, "=_stub_");
        PrintName(fileDest, pexp, &pexp->strName, 0);
    }
    else if (pexp->strTarget.buf)
    {
        if (pexp->strName.buf[0] == '?')
        {
            //fprintf(stderr, "warning: ignoring C++ redirection %.*s -> %.*s\n",
            //        pexp->strName.len, pexp->strName.buf, pexp->strTarget.len, pexp->strTarget.buf);
        }
        else
        {
            fprintf(fileDest, "=");

            /* If the original name was decorated, use decoration in the forwarder as well */
            if ((giArch == ARCH_X86) && ScanToken(pexp->strName.buf, '@') &&
                !ScanToken(pexp->strTarget.buf, '@') &&
                ((pexp->nCallingConvention == CC_STDCALL) ||
                (pexp->nCallingConvention == CC_FASTCALL)) )
            {
                PrintName(fileDest, pexp, &pexp->strTarget, 1);
            }
            else
            {
                /* Write the undecorated redirection name */
                fprintf(fileDest, "%.*s", pexp->strTarget.len, pexp->strTarget.buf);
            }
        }
    }
    else if (((pexp->uFlags & FL_STUB) || (pexp->nCallingConvention == CC_STUB)) &&
             (pexp->strName.buf[0] == '?'))
    {
        /* C++ stubs are forwarded to C stubs */
        fprintf(fileDest, "=stub_function%d", pexp->nNumber);
    }
    else if (gbTracing && ((pexp->uFlags & FL_NORELAY) == 0) && (pexp->nCallingConvention == CC_STDCALL) &&
            (pexp->strName.buf[0] != '?'))
    {
        /* Redirect it to the relay-tracing trampoline */
        fprintf(fileDest, "=$relaytrace$%.*s", pexp->strName.len, pexp->strName.buf);
    }
}