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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int Grouping; char* lpDecimalSep; char* lpThousandSep; scalar_t__ NegativeOrder; scalar_t__ LeadingZero; scalar_t__ NumDigits; } ;
typedef  TYPE_1__ NUMBERFMTW ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 scalar_t__ BUFFER_SIZE ; 
 unsigned int GetNumberFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  _itow (unsigned int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static
VOID
FormatBytes(LPWSTR lpBuf, unsigned cBytes)
{
    WCHAR szMB[32];
    NUMBERFMTW fmt;
    unsigned i;

    _itow(cBytes / (1024*1024), szMB, 10);

    fmt.NumDigits = 0;
    fmt.LeadingZero = 0;
    fmt.Grouping = 3;
    fmt.lpDecimalSep = L"";
    fmt.lpThousandSep = L" ";
    fmt.NegativeOrder = 0;

    i = GetNumberFormatW(LOCALE_SYSTEM_DEFAULT, 0, szMB, &fmt, lpBuf, BUFFER_SIZE - 3);
    if (i)
        --i; /* don't count NULL character */
    wcscpy(lpBuf + i, L" MB");
}