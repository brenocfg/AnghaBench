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
typedef  int /*<<< orphan*/  list ;
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static char *get_temp_buffer( int size )
{
    static char *list[32];
    static UINT pos;
    char *ret;
    UINT idx;

    idx = ++pos % (sizeof(list)/sizeof(list[0]));
    if (list[idx])
        ret = HeapReAlloc( GetProcessHeap(), 0, list[idx], size );
    else
        ret = HeapAlloc( GetProcessHeap(), 0, size );
    if (ret) list[idx] = ret;
    return ret;
}