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
typedef  size_t UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 

__attribute__((used)) static void
AcpiRsDumpShortByteList (
    UINT8                   Length,
    UINT8                   *Data)
{
    UINT8                   i;


    for (i = 0; i < Length; i++)
    {
        AcpiOsPrintf ("%X ", Data[i]);
    }

    AcpiOsPrintf ("\n");
}