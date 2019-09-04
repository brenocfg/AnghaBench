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
typedef  int USHORT ;
struct TYPE_3__ {int Length; int /*<<< orphan*/  Buffer; } ;
typedef  int* PUSHORT ;
typedef  TYPE_1__* PUNICODE_STRING ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
Ext2IsNameValid(PUNICODE_STRING FileName)
{
    USHORT  i = 0;
    PUSHORT pName = (PUSHORT) FileName->Buffer;

    if (FileName == NULL) {
        return FALSE;
    }

    while (i < (FileName->Length / sizeof(WCHAR))) {

        if (pName[i] == 0) {
            break;
        }

        if (pName[i] == L'|'  || pName[i] == L':'  ||
                pName[i] == L'/'  || pName[i] == L'*'  ||
                pName[i] == L'?'  || pName[i] == L'\"' ||
                pName[i] == L'<'  || pName[i] == L'>'   ) {

            return FALSE;
        }

        i++;
    }

    return TRUE;
}