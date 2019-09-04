#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stub_msg ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int CorrDespIncrement; } ;
typedef  TYPE_1__ MIDL_STUB_MESSAGE ;
typedef  TYPE_1__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  NdrCorrelationInitialize (TYPE_1__*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_NdrCorrelationInitialize(void)
{
    MIDL_STUB_MESSAGE stub_msg;
    BYTE buf[256];

    memset( &stub_msg, 0, sizeof(stub_msg) );
    memset( buf, 0, sizeof(buf) );

    NdrCorrelationInitialize( &stub_msg, buf, sizeof(buf), 0 );
    ok( stub_msg.CorrDespIncrement == 2 ||
        broken(stub_msg.CorrDespIncrement == 0), /* <= Win 2003 */
        "got %d\n", stub_msg.CorrDespIncrement );

    memset( &stub_msg, 0, sizeof(stub_msg) );
    memset( buf, 0, sizeof(buf) );

    stub_msg.CorrDespIncrement = 1;
    NdrCorrelationInitialize( &stub_msg, buf, sizeof(buf), 0 );
    ok( stub_msg.CorrDespIncrement == 1, "got %d\n", stub_msg.CorrDespIncrement );
}