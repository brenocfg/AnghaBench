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
typedef  int UINT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  CHINESEBIG5_CHARSET 131 
 int /*<<< orphan*/  FALSE ; 
#define  GB2312_CHARSET 130 
#define  HANGUL_CHARSET 129 
#define  SHIFTJIS_CHARSET 128 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL is_cjk(UINT charset)
{
    switch(charset)
    {
    case SHIFTJIS_CHARSET:
    case HANGUL_CHARSET:
    case GB2312_CHARSET:
    case CHINESEBIG5_CHARSET:
        return TRUE;
    }
    /* HANGUL_CHARSET is strange, though treated as CJK by Win 8, it is
     * not by other versions including Win 10. */
    return FALSE;
}