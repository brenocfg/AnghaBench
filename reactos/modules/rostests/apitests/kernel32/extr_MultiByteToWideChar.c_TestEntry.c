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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {scalar_t__ DestLen; char const* Src; int CheckLen; int Return; int /*<<< orphan*/ * CheckDest; int /*<<< orphan*/  LineNo; int /*<<< orphan*/  Error; int /*<<< orphan*/  SrcLen; int /*<<< orphan*/  Flags; int /*<<< orphan*/  CodePage; scalar_t__ SamePointer; } ;
typedef  TYPE_1__ ENTRY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  FillMemory (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_BUFFER ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void TestEntry(const ENTRY *pEntry)
{
    int ret, i;
    WCHAR Buffer[MAX_BUFFER];
    DWORD Error;

    FillMemory(Buffer, sizeof(Buffer), 0x7F);
    SetLastError(0xBEAF);

    if (pEntry->DestLen == 0)
    {
        /* dest is NULL */
        ret = MultiByteToWideChar(pEntry->CodePage, pEntry->Flags, pEntry->Src,
                                  pEntry->SrcLen, NULL, 0);
    }
    else
    {
        ok(pEntry->DestLen >= pEntry->CheckLen - 1,
           "Line %d: DestLen was shorter than (CheckLen - 1)\n", pEntry->LineNo);

        if (pEntry->SamePointer)
        {
            /* src ptr == dest ptr */
            ret = MultiByteToWideChar(pEntry->CodePage, pEntry->Flags,
                                      (const char *)Buffer, pEntry->SrcLen,
                                      Buffer, pEntry->DestLen);
        }
        else
        {
            /* src ptr != dest ptr */
            ret = MultiByteToWideChar(pEntry->CodePage, pEntry->Flags,
                                      pEntry->Src, pEntry->SrcLen,
                                      Buffer, pEntry->DestLen);
        }
    }

    Error = GetLastError();

    /* check ret */
    ok(ret == pEntry->Return, "Line %d: ret expected %d, got %d\n",
       pEntry->LineNo, pEntry->Return, ret);

    /* check error code */
    ok(Error == pEntry->Error,
       "Line %d: Wrong last error. Expected %lu, got %lu\n",
       pEntry->LineNo, pEntry->Error, Error);

    if (pEntry->DestLen)
    {
        /* check buffer */
        for (i = 0; i < pEntry->CheckLen; ++i)
        {
            ok(Buffer[i] == pEntry->CheckDest[i], "Line %d: Buffer[%d] expected %d, got %d\n",
               pEntry->LineNo, i, pEntry->CheckDest[i], Buffer[i]);
        }
    }
}