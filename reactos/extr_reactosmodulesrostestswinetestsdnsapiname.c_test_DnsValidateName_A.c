#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ status; scalar_t__ status_broken; int /*<<< orphan*/ * name; int /*<<< orphan*/  format; } ;
typedef  scalar_t__ DNS_STATUS ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DnsNameDomain ; 
 scalar_t__ DnsValidateName_A (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INVALID_NAME ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 TYPE_1__* test_data ; 

__attribute__((used)) static void test_DnsValidateName_A( void )
{
    unsigned int i;
    DNS_STATUS status;

    status = DnsValidateName_A( NULL, DnsNameDomain );
    ok( status == ERROR_INVALID_NAME, "succeeded unexpectedly\n" );

    for (i = 0; i < ARRAY_SIZE(test_data); i++)
    {
        status = DnsValidateName_A( test_data[i].name, test_data[i].format );
        ok( status == test_data[i].status || broken(status == test_data[i].status_broken),
            "%d: \'%s\': got %d, expected %d\n", i, test_data[i].name, status, test_data[i].status );
    }
}