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
typedef  size_t* LPCWSTR ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int* table_dec85 ; 

BOOL decode_base85_guid( LPCWSTR str, GUID *guid )
{
    DWORD i, val = 0, base = 1, *p;

    if (!str)
        return FALSE;

    p = (DWORD*) guid;
    for( i=0; i<20; i++ )
    {
        if( (i%5) == 0 )
        {
            val = 0;
            base = 1;
        }
        val += table_dec85[str[i]] * base;
        if( str[i] >= 0x80 )
            return FALSE;
        if( table_dec85[str[i]] == 0xff )
            return FALSE;
        if( (i%5) == 4 )
            p[i/5] = val;
        base *= 85;
    }
    return TRUE;
}