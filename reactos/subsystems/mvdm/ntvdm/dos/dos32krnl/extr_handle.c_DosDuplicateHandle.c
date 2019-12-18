#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_2__ {int /*<<< orphan*/  LastErrorCode; } ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DosOpenHandle (int) ; 
 int DosQueryHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  INVALID_DOS_HANDLE ; 
 TYPE_1__* Sda ; 

WORD DosDuplicateHandle(WORD DosHandle)
{
    BYTE DescriptorId = DosQueryHandle(DosHandle);

    if (DescriptorId == 0xFF)
    {
        Sda->LastErrorCode = ERROR_INVALID_HANDLE;
        return INVALID_DOS_HANDLE;
    }

    return DosOpenHandle(DescriptorId);
}