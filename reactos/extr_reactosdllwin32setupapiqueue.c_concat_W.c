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

/* Variables and functions */
 int /*<<< orphan*/  strcpyW (char*,char const*) ; 
 int /*<<< orphan*/  strlenW (char*) ; 

__attribute__((used)) static void concat_W( WCHAR *buffer, const WCHAR *src1, const WCHAR *src2, const WCHAR *src3 )
{
    *buffer = 0;
    if (src1 && *src1)
    {
        strcpyW( buffer, src1 );
        buffer += strlenW(buffer );
        if (buffer[-1] != '\\') *buffer++ = '\\';
        if (src2) while (*src2 == '\\') src2++;
    }

    if (src2)
    {
        strcpyW( buffer, src2 );
        buffer += strlenW(buffer );
        if (buffer[-1] != '\\') *buffer++ = '\\';
        if (src3) while (*src3 == '\\') src3++;
    }

    if (src3)
        strcpyW( buffer, src3 );
}