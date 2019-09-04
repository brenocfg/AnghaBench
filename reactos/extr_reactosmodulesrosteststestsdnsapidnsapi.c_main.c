#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  IpAddress; } ;
struct TYPE_7__ {TYPE_1__ A; } ;
struct TYPE_8__ {scalar_t__ wType; struct TYPE_8__* pNext; TYPE_2__ Data; } ;
typedef  TYPE_3__* PDNS_RECORD ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ DNS_ERROR_INVALID_NAME ; 
 scalar_t__ DNS_ERROR_INVALID_NAME_CHAR ; 
 int /*<<< orphan*/  DNS_QUERY_STANDARD ; 
 scalar_t__ DNS_TYPE_A ; 
 int /*<<< orphan*/  DnsFreeRecordList ; 
 int /*<<< orphan*/  DnsNameDomain ; 
 int /*<<< orphan*/  DnsNameDomainLabel ; 
 scalar_t__ DnsQuery (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DnsRecordListFree (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ DnsValidateName (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 

int main( int argc, char **argv ) {
  PDNS_RECORD QueryReply, AddrResponse;
  DWORD Addr;

  assert (DnsValidateName( "||||", DnsNameDomain ) == DNS_ERROR_INVALID_NAME_CHAR);
  assert (DnsValidateName( "a.b.c", DnsNameDomainLabel ) == DNS_ERROR_INVALID_NAME);
  assert (DnsValidateName( "1234", DnsNameDomainLabel ) == ERROR_SUCCESS);
  assert (DnsValidateName( "fubar", DnsNameDomain ) == ERROR_SUCCESS);
  assert (DnsQuery ("www.reactos.com", DNS_TYPE_A, DNS_QUERY_STANDARD,
		    NULL, &QueryReply, NULL) == ERROR_SUCCESS);
  AddrResponse = QueryReply;
  while( AddrResponse ) {
    if( AddrResponse->wType == DNS_TYPE_A ) {
      Addr = ntohl( AddrResponse->Data.A.IpAddress );
      printf( "www.reactos.com == %d.%d.%d.%d\n",
	      (int)(Addr >> 24) & 0xff,
	      (int)(Addr >> 16) & 0xff,
	      (int)(Addr >> 8) & 0xff,
	      (int)Addr & 0xff );
    }
    AddrResponse = AddrResponse->pNext;
  }
  DnsRecordListFree( QueryReply, DnsFreeRecordList );

  return 0;
}