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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  is_text_plain_char (int /*<<< orphan*/  const) ; 

__attribute__((used)) static BOOL text_plain_filter(const BYTE *b, DWORD size)
{
    const BYTE *ptr;

    for(ptr = b; ptr < b+size-1; ptr++) {
        if(!is_text_plain_char(*ptr))
            return FALSE;
    }

    return TRUE;
}