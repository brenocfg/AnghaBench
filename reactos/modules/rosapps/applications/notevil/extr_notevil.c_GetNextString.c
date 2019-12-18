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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__* PDWORD ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RES_FIRST_INDEX ; 
 scalar_t__ RES_LAST_INDEX ; 
 int /*<<< orphan*/  myself ; 

VOID
GetNextString(LPWSTR Buffer,
              INT    BufferSize,
              PDWORD Index)
{
    if (RES_LAST_INDEX == *Index)
        *Index = RES_FIRST_INDEX;
    else
        ++*Index;

    LoadStringW(myself, *Index, Buffer, BufferSize);
}