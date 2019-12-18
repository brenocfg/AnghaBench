#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ IpAddress; } ;
struct TYPE_12__ {TYPE_3__ A; } ;
struct TYPE_9__ {void* CharSet; } ;
struct TYPE_10__ {TYPE_1__ S; } ;
struct TYPE_13__ {TYPE_4__ Data; scalar_t__ dwTtl; TYPE_2__ Flags; int /*<<< orphan*/  pName; } ;

/* Variables and functions */
 void* DnsCharSetAnsi ; 
 void* DnsCharSetUnicode ; 
 scalar_t__ DnsRecordCompare (TYPE_5__*,TYPE_5__*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  name2 ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 TYPE_5__ r1 ; 
 TYPE_5__ r2 ; 

__attribute__((used)) static void test_DnsRecordCompare( void )
{
    ok( DnsRecordCompare( &r1, &r1 ) == TRUE, "failed unexpectedly\n" );

    r2.pName = name2;
    ok( DnsRecordCompare( &r1, &r2 ) == TRUE, "failed unexpectedly\n" );

    r2.Flags.S.CharSet = DnsCharSetUnicode;
    ok( DnsRecordCompare( &r1, &r2 ) == TRUE, "failed unexpectedly\n" );

    r2.Flags.S.CharSet = DnsCharSetAnsi;
    ok( DnsRecordCompare( &r1, &r2 ) == TRUE, "failed unexpectedly\n" );

    r1.Flags.S.CharSet = DnsCharSetAnsi;
    ok( DnsRecordCompare( &r1, &r2 ) == TRUE, "failed unexpectedly\n" );

    r1.dwTtl = 0;
    ok( DnsRecordCompare( &r1, &r2 ) == TRUE, "failed unexpectedly\n" );

    r2.Data.A.IpAddress = 0;
    ok( DnsRecordCompare( &r1, &r2 ) == FALSE, "succeeded unexpectedly\n" );
}