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
typedef  scalar_t__* LPSTR ;
typedef  int /*<<< orphan*/  CERT_ENHKEY_USAGE ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * add_oid_to_usage (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__* strchr (scalar_t__*,char) ; 

__attribute__((used)) static CERT_ENHKEY_USAGE *convert_usages_str_to_usage(LPSTR usageStr)
{
    CERT_ENHKEY_USAGE *usage = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
     sizeof(CERT_ENHKEY_USAGE));

    if (usage)
    {
        LPSTR ptr, comma;

        for (ptr = usageStr, comma = strchr(ptr, ','); usage && ptr && *ptr;
         ptr = comma ? comma + 1 : NULL,
         comma = ptr ? strchr(ptr, ',') : NULL)
        {
            if (comma)
                *comma = 0;
            usage = add_oid_to_usage(usage, ptr);
        }
    }
    return usage;
}