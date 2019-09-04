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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  PULONG ;

/* Variables and functions */
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TiGetProtocolNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _AssertEqualValue (int,int) ; 

__attribute__((used)) static void RunTest() {
    UNICODE_STRING Str;
    int Proto;
    RtlInitUnicodeString( &Str, L"1" );
    TiGetProtocolNumber( &Str, (PULONG)&Proto );
    _AssertEqualValue(1, Proto);
}