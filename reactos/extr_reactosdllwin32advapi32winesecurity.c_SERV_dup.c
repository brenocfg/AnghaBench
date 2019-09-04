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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 

__attribute__((used)) static LPWSTR SERV_dup( LPCSTR str )
{
    UINT len;
    LPWSTR wstr;

    if( !str )
        return NULL;
    len = MultiByteToWideChar( CP_ACP, 0, str, -1, NULL, 0 );
    wstr = heap_alloc( len*sizeof (WCHAR) );
    MultiByteToWideChar( CP_ACP, 0, str, -1, wstr, len );
    return wstr;
}