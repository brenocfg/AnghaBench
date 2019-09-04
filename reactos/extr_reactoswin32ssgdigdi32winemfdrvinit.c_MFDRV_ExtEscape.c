#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_5__ {int rdSize; int* rdParm; int /*<<< orphan*/  rdFunction; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  TYPE_1__ METARECORD ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  int INT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  META_ESCAPE ; 
 int MFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static INT MFDRV_ExtEscape( PHYSDEV dev, INT nEscape, INT cbInput, LPCVOID in_data,
                            INT cbOutput, LPVOID out_data )
{
    METARECORD *mr;
    DWORD len;
    INT ret;

    if (cbOutput) return 0;  /* escapes that require output cannot work in metafiles */

    len = sizeof(*mr) + sizeof(WORD) + ((cbInput + 1) & ~1);
    mr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len);
    mr->rdSize = len / 2;
    mr->rdFunction = META_ESCAPE;
    mr->rdParm[0] = nEscape;
    mr->rdParm[1] = cbInput;
    memcpy(&(mr->rdParm[2]), in_data, cbInput);
    ret = MFDRV_WriteRecord( dev, mr, len);
    HeapFree(GetProcessHeap(), 0, mr);
    return ret;
}