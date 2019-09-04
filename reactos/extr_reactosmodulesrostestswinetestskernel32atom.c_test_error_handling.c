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
 int /*<<< orphan*/  GlobalAddAtomA (char*) ; 
 int /*<<< orphan*/  GlobalAddAtomW (char*) ; 
 int /*<<< orphan*/  GlobalFindAtomA (char*) ; 
 int /*<<< orphan*/  GlobalFindAtomW (char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ unicode_OS ; 

__attribute__((used)) static void test_error_handling(void)
{
    char buffer[260];
    WCHAR bufferW[260];
    int i;

    memset( buffer, 'a', 256 );
    buffer[256] = 0;
    ok( !GlobalAddAtomA(buffer), "add succeeded\n" );
    ok( !GlobalFindAtomA(buffer), "find succeeded\n" );

    if (unicode_OS)
    {
        for (i = 0; i < 256; i++) bufferW[i] = 'b';
        bufferW[256] = 0;
        ok( !GlobalAddAtomW(bufferW), "add succeeded\n" );
        ok( !GlobalFindAtomW(bufferW), "find succeeded\n" );
    }
}