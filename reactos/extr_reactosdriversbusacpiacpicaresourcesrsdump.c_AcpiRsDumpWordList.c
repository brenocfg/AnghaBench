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
typedef  size_t UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiOsPrintf (char*,char*,size_t,size_t) ; 

__attribute__((used)) static void
AcpiRsDumpWordList (
    UINT16                  Length,
    UINT16                  *Data)
{
    UINT16                  i;


    for (i = 0; i < Length; i++)
    {
        AcpiOsPrintf ("%25s%2.2X : %4.4X\n", "Word", i, Data[i]);
    }
}