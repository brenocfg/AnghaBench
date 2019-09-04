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
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiUtRemoveHexPrefix (char**) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
AcpiUtDetectHexPrefix (
    char                    **String)
{
    char                    *InitialPosition = *String;

    AcpiUtRemoveHexPrefix (String);
    if (*String != InitialPosition)
    {
        return (TRUE); /* String is past leading 0x */
    }

    return (FALSE);     /* Not a hex string */
}