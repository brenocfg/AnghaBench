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
typedef  int ULONG ;
typedef  int* PULONG ;
typedef  int* LPSTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int StrLenUpToWhiteChar (int*,char*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN ConvertSizeToKeyword(LPSTR p,PULONG pValue)
{
    ULONG count;

	count=StrLenUpToWhiteChar(p," ");
    if(count > 1)
	    return FALSE;

    switch(*p)
    {
        // BYTE
        case 'b':
        case 'B':
            *pValue = 1;
            break;
        // WORD
        case 'w':
        case 'W':
            *pValue = 2;
            break;
        // DWORD
        case 'd':
        case 'D':
            *pValue = 4;
            break;
        // QWORD
        case 'q':
        case 'Q':
            *pValue = 4;
            break;
        default:
            return FALSE;
    }

    return TRUE;
}