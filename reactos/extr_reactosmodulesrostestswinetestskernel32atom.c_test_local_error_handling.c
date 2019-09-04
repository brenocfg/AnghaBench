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
 int /*<<< orphan*/  AddAtomA (char*) ; 
 int /*<<< orphan*/  AddAtomW (char*) ; 
 int /*<<< orphan*/  FindAtomA (char*) ; 
 int /*<<< orphan*/  FindAtomW (char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ unicode_OS ; 

__attribute__((used)) static void test_local_error_handling(void)
{
    char buffer[260];
    WCHAR bufferW[260];
    int i;

    memset( buffer, 'a', 256 );
    buffer[256] = 0;
    ok( !AddAtomA(buffer), "add succeeded\n" );
    ok( !FindAtomA(buffer), "find succeeded\n" );

    if (unicode_OS)
    {
        for (i = 0; i < 256; i++) bufferW[i] = 'b';
        bufferW[256] = 0;
        ok( !AddAtomW(bufferW), "add succeeded\n" );
        ok( !FindAtomW(bufferW), "find succeeded\n" );
    }
}