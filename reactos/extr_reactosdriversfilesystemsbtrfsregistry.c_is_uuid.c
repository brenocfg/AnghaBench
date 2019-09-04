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
typedef  char WCHAR ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  is_hex (char) ; 

__attribute__((used)) static BOOL is_uuid(ULONG namelen, WCHAR* name) {
    ULONG i;

    if (namelen != 36 * sizeof(WCHAR))
        return FALSE;

    for (i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            if (name[i] != '-')
                return FALSE;
        } else if (!is_hex(name[i]))
            return FALSE;
    }

    return TRUE;
}