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
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int DWORD ;

/* Variables and functions */
 int lstrlenA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_dword (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static DWORD write_string( LPBYTE data, DWORD ofs, LPCSTR str )
{
    DWORD len = lstrlenA( str ) + 1;
    write_dword( data, ofs, len );
    if( data )
        memcpy( &data[ofs + 4], str, len );
    return (7 + len) & ~3;
}