#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PULONG ;
typedef  int LPSTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ReadHex (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN ScanExportLine(LPSTR p,PULONG ulValue,LPSTR* ppPtrToSymbol)
{
    BOOLEAN bResult = FALSE;

    if(ReadHex(p,ulValue))
    {
        p += 11;
        *ppPtrToSymbol += 11;
        bResult = TRUE;
    }

    return bResult;
}