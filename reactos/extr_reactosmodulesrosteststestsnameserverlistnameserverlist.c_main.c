#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {int /*<<< orphan*/  String; } ;
struct TYPE_8__ {TYPE_1__ IpAddress; struct TYPE_8__* Next; } ;
struct TYPE_9__ {TYPE_2__* CurrentDnsServer; TYPE_2__ DnsServerList; } ;
typedef  TYPE_2__* PIP_ADDR_STRING ;
typedef  TYPE_3__* PFIXED_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetNetworkParams (TYPE_3__*,scalar_t__*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* malloc (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char,...) ; 

int main( int argc, char **argv ) {
  ULONG OutBufLen = 0;
  PFIXED_INFO pFixedInfo;
  PIP_ADDR_STRING Addr;

  GetNetworkParams(NULL, &OutBufLen);
  pFixedInfo = malloc(OutBufLen);
  if (!pFixedInfo) {
    printf( "Failed to alloc %d bytes.\n", (int)OutBufLen );
    return 1;
  }

  printf( "%d Bytes allocated\n", (int)OutBufLen );

  GetNetworkParams(pFixedInfo,&OutBufLen);

  for( Addr = &pFixedInfo->DnsServerList;
       Addr;
       Addr = Addr->Next ) {
    printf( "%c%s\n",
	    Addr == pFixedInfo->CurrentDnsServer ? '*' : ' ',
	    Addr->IpAddress.String );
  }

  free( pFixedInfo );
  return 0;
}