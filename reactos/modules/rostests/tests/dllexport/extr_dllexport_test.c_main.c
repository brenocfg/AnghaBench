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

/* Variables and functions */
 int /*<<< orphan*/  CdeclFunc0 () ; 
 int /*<<< orphan*/  CdeclFunc1 (char*) ; 
 int /*<<< orphan*/  CdeclFunc2 (char*) ; 
 int /*<<< orphan*/  CdeclFunc3 (char*) ; 
 int /*<<< orphan*/  DataItem1 ; 
 int /*<<< orphan*/  DataItem2 ; 
 int /*<<< orphan*/  DataItem3 ; 
 int /*<<< orphan*/  DecoratedFastcallFunc1 (char*) ; 
 int /*<<< orphan*/  DecoratedFastcallFunc2 (char*) ; 
 int /*<<< orphan*/  DecoratedFastcallFunc4 (char*) ; 
 int /*<<< orphan*/  DecoratedFastcallFunc5 (char*) ; 
 int /*<<< orphan*/  DecoratedStdcallFunc1 (char*) ; 
 int /*<<< orphan*/  DecoratedStdcallFunc2 (char*) ; 
 int /*<<< orphan*/  DecoratedStdcallFunc4 (char*) ; 
 int /*<<< orphan*/  DecoratedStdcallFunc5 (char*) ; 
 int /*<<< orphan*/  FastcallFunc0 () ; 
 int /*<<< orphan*/  FastcallFunc1 (char*) ; 
 int /*<<< orphan*/  FastcallFunc2 (char*) ; 
 int /*<<< orphan*/  FastcallFunc3 (char*) ; 
 int /*<<< orphan*/  FastcallFunc4 (char*) ; 
 int /*<<< orphan*/  FastcallFunc5 (char*) ; 
 int /*<<< orphan*/  StdcallFunc0 () ; 
 int /*<<< orphan*/  StdcallFunc1 (char*) ; 
 int /*<<< orphan*/  StdcallFunc2 (char*) ; 
 int /*<<< orphan*/  StdcallFunc3 (char*) ; 
 int /*<<< orphan*/  StdcallFunc4 (char*) ; 
 int /*<<< orphan*/  StdcallFunc5 (char*) ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main(int argc, char *argv[])
{
    char* str = "defaultstring";

    if (argc > 2)
        str = argv[1];

    ok_int(CdeclFunc0(), 0);
    ok_int(CdeclFunc1(str), 1);
    ok_int(CdeclFunc2(str), 1);
    ok_int(CdeclFunc3(str), 0x10001);

    ok_int(StdcallFunc0(), 0x10);
    ok_int(StdcallFunc1(str), 0x11);
    ok_int(StdcallFunc2(str), 0x11);
    ok_int(StdcallFunc3(str), 0x10011);
#ifdef _M_IX86
    ok_int(StdcallFunc4(str), 0x21);
#endif
    ok_int(StdcallFunc5(str), 0x10021);

#ifdef _M_IX86
    ok_int(DecoratedStdcallFunc1(str), 0x21);
    ok_int(DecoratedStdcallFunc2(str), 0x11);
    //ok_int(DecoratedStdcallFunc3(str), 11);
    ok_int(DecoratedStdcallFunc4(str), 0x21);
    ok_int(DecoratedStdcallFunc5(str), 0x10021);
#endif
    ok_int(FastcallFunc0(), 0x30);
    ok_int(FastcallFunc1(str), 0x31);
    ok_int(FastcallFunc2(str), 0x31);
    ok_int(FastcallFunc3(str), 0x10031);
#ifdef _M_IX86
    ok_int(FastcallFunc4(str), 0x42);
    ok_int(FastcallFunc5(str), 0x10041);
#endif
#ifdef _M_IX86
    ok_int(DecoratedFastcallFunc1(str), 0x42);
    ok_int(DecoratedFastcallFunc2(str), 0x31);
    //ok_int(DecoratedFastcallFunc3(str), 11);
    ok_int(DecoratedFastcallFunc4(str), 0x42);
    ok_int(DecoratedFastcallFunc5(str), 0x10041);
#endif
    ok_int(DataItem1, 0x51);
    ok_int(DataItem2, 0x51);
    ok_int(DataItem3, 0x10051);

    printf("done.\n");

    return 0;
}