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
typedef  scalar_t__ u8b ;
typedef  int /*<<< orphan*/  u32b ;
struct TYPE_3__ {int* chaddr; scalar_t__ xid; int /*<<< orphan*/  available; struct TYPE_3__* next; } ;
typedef  TYPE_1__ DHCPLIST ;
typedef  int /*<<< orphan*/  DHCPLEASE ;

/* Variables and functions */
 int /*<<< orphan*/  FREE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int,int,int) ; 
 TYPE_1__* list ; 
 int /*<<< orphan*/  maccmp (int*,scalar_t__*) ; 
 int /*<<< orphan*/  stdout ; 

int release_lease( DHCPLEASE *dhcpl, u32b xid, u8b chaddr[16] )
{
  int result = -1, i;
  DHCPLIST *temp;
  u8b nchaddr[16];

  for( i = 0; i < 16; i++ )
    nchaddr[i] = 0;

  if( !dhcpl )
    return -1;

  for( temp = list; temp; temp=temp->next )
    if( !maccmp( temp->chaddr, chaddr ) )
      {
	/* We found the address */
	result = 0;
	fprintf( stdout, "Deleting %X::%X::%X::%X::%X::%X \n", temp->chaddr[0], temp->chaddr[1], temp->chaddr[2], temp->chaddr[3], temp->chaddr[4], temp->chaddr[5] );
	temp->available = FREE;
	temp->xid = 0;
	/*	maccpy( temp->chaddr, nchaddr ); */
      } else {
	/* No such address */
	result = -1;
      }

  return result;
}