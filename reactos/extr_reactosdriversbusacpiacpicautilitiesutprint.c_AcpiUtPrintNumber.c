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
typedef  int /*<<< orphan*/  UINT64 ;

/* Variables and functions */
 char* AcpiUtPutNumber (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 

const char *
AcpiUtPrintNumber (
    char                    *String,
    UINT64                  Number)
{
    char                    AsciiString[20];
    const char              *Pos1;
    char                    *Pos2;


    Pos1 = AcpiUtPutNumber (AsciiString, Number, 10, FALSE);
    Pos2 = String;

    while (Pos1 != AsciiString)
    {
        *(Pos2++) = *(--Pos1);
    }

    *Pos2 = 0;
    return (String);
}