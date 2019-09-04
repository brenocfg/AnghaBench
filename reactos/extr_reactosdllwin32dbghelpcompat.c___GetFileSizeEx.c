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
struct TYPE_3__ {int /*<<< orphan*/  QuadPart; } ;
typedef  TYPE_1__* PLARGE_INTEGER ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ftell (int /*<<< orphan*/ *) ; 

BOOL __GetFileSizeEx(HANDLE file, PLARGE_INTEGER fsize)
{
    if (fseek((FILE*)file, 0, 2) == -1)
        return FALSE;
    fsize->QuadPart = ftell((FILE*)file);
    return TRUE;
}