#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int ip; int siaddr; int router; int mask; int lease; } ;
struct TYPE_12__ {int yiaddr; int siaddr; char* sname; int* options; int ciaddr; int /*<<< orphan*/  xid; void* op; int /*<<< orphan*/  chaddr; } ;
struct TYPE_11__ {int type; } ;
typedef  TYPE_1__ DHCPOPTIONS ;
typedef  TYPE_2__ DHCPMESSAGE ;
typedef  TYPE_3__ DHCPLEASE ;

/* Variables and functions */
 void* BOOTREPLY ; 
 void* DHCPACK ; 
#define  DHCPDISCOVER 129 
 int DHCPNAK ; 
 void* DHCPOFFER ; 
#define  DHCPREQUEST 128 
 void* END ; 
 void* LEASE ; 
 void* MASK ; 
 void* MESSAGETYPE ; 
 void* PAD ; 
 void* REBINDING ; 
 void* RENEWALTIME ; 
 void* ROUTER ; 
 void* SERVER ; 
 char* VERSION ; 
 int /*<<< orphan*/  confirm_lease (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_dhcp_packet (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  find_lease (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  write_packet (TYPE_2__*,char*) ; 

int process_dhcp_packet( DHCPMESSAGE *dhcpm, DHCPOPTIONS *dhcpo )
{
  int pointer = 4;
  DHCPLEASE dhcpl;
  char *name;

  fprintf( stdout, "process_dhcp_packet [begin]!\n");

  if( (!dhcpm) || (!dhcpo) )
    return -1;

  name = (char *)malloc( 16 );
  switch( dhcpo->type ){

  case DHCPDISCOVER:
    /* We need to send a DHCPOFFER */
    if( find_lease( &dhcpl, dhcpm->xid, dhcpm->chaddr ) < 0 )
      {
	fprintf( stdout, "No free leases! \n" );
	free( name );
	return -1;
      }
    dhcpm->op = BOOTREPLY;
    dhcpm->yiaddr = dhcpl.ip;
    dhcpm->siaddr = dhcpl.siaddr;
    strcpy(dhcpm->sname, VERSION);
    dhcpm->options[pointer++] = MESSAGETYPE;
    dhcpm->options[pointer++] = 1;
    dhcpm->options[pointer++] = DHCPOFFER;
    dhcpm->options[pointer++] = ROUTER;
    dhcpm->options[pointer++] = 4;
    dhcpm->options[pointer++] = (dhcpl.router & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.router >> 8) & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.router >> 16) &0xFF);
    dhcpm->options[pointer++] = (dhcpl.router >> 24);
    dhcpm->options[pointer++] = MASK;
    dhcpm->options[pointer++] = 4;
    dhcpm->options[pointer++] = (dhcpl.mask & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.mask >> 8) & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.mask >> 16) & 0xFF);
    dhcpm->options[pointer++] = (dhcpl.mask >> 24);
    dhcpm->options[pointer++] = SERVER;
    dhcpm->options[pointer++] = 4;
    dhcpm->options[pointer++] = (dhcpl.siaddr & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.siaddr >> 8) & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.siaddr >> 16) & 0xFF);
    dhcpm->options[pointer++] = (dhcpl.siaddr >> 24);
    dhcpm->options[pointer++] = LEASE;
    dhcpm->options[pointer++] = 4;
    dhcpm->options[pointer++] = (dhcpl.lease >> 24);
    dhcpm->options[pointer++] = ((dhcpl.lease >> 16) & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.lease >> 8) & 0xFF);
    dhcpm->options[pointer++] = (dhcpl.lease & 0xFF);
    dhcpm->options[pointer++] = REBINDING;
    dhcpm->options[pointer++] = 4;
    dhcpm->options[pointer++] = (dhcpl.lease >> 24);
    dhcpm->options[pointer++] = ((dhcpl.lease >> 16) & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.lease >> 8) & 0xFF);
    dhcpm->options[pointer++] = (dhcpl.lease & 0xFF) - 5;
    dhcpm->options[pointer++] = RENEWALTIME;
    dhcpm->options[pointer++] = 4;
    dhcpm->options[pointer++] = (dhcpl.lease >> 24);
    dhcpm->options[pointer++] = ((dhcpl.lease >> 16) & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.lease >> 8) & 0xFF);
    dhcpm->options[pointer++] = (dhcpl.lease & 0xFF) - 5;
    dhcpm->options[pointer++] = PAD;
    dhcpm->options[pointer++] = PAD;
    dhcpm->options[pointer++] = PAD;
    dhcpm->options[pointer++] = END;
    for( ; pointer < 312; pointer++ )
      dhcpm->options[pointer] = PAD;
    dhcpo->type = DHCPOFFER;
    strcpy( name, "255.255.255.255" );
    break;

  case DHCPREQUEST:
    /* We need to send an DHCPACK */
    dhcpm->op = BOOTREPLY;
    dhcpm->yiaddr = dhcpm->ciaddr;
    strcpy(dhcpm->sname, VERSION);
    if( confirm_lease( &dhcpl, dhcpm->xid ) < 0)
      {
	dhcpm->options[pointer++] = MESSAGETYPE;
	dhcpm->options[pointer++] = 1;
	dhcpm->options[pointer++] = DHCPNAK;
	dhcpm->options[pointer++] = PAD;
	dhcpm->options[pointer++] = END;
	for( ; pointer < 312; pointer++ )
	  dhcpm->options[pointer] = PAD;
	sprintf( name, "%u.%u.%u.%u", (dhcpm->ciaddr &0xFF), ((dhcpm->ciaddr>>8)&0xFF), ((dhcpm->ciaddr>>16)&0xFF), ((dhcpm->ciaddr>>24)&0xFF));
	display_dhcp_packet( dhcpm, dhcpo );
	write_packet( dhcpm, name );
	free( name );
	return -1;
      }
    dhcpm->siaddr = dhcpl.siaddr;
    dhcpm->options[pointer++] = MESSAGETYPE;
    dhcpm->options[pointer++] = 1;
    dhcpm->options[pointer++] = DHCPACK;
    dhcpm->options[pointer++] = ROUTER;
    dhcpm->options[pointer++] = 4;
    dhcpm->options[pointer++] = (dhcpl.router >> 24);
    dhcpm->options[pointer++] = ((dhcpl.router >> 16) & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.router >> 8) &0xFF);
    dhcpm->options[pointer++] = (dhcpl.router & 0xFF);
    dhcpm->options[pointer++] = MASK;
    dhcpm->options[pointer++] = 4;
    dhcpm->options[pointer++] = (dhcpl.mask >> 24);
    dhcpm->options[pointer++] = ((dhcpl.mask >> 16) & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.mask >> 8) & 0xFF);
    dhcpm->options[pointer++] = (dhcpl.mask & 0xFF);
    dhcpm->options[pointer++] = SERVER;
    dhcpm->options[pointer++] = 4;
    dhcpm->options[pointer++] = dhcpl.siaddr >> 24;
    dhcpm->options[pointer++] = ((dhcpl.siaddr >> 16) & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.siaddr >> 8) & 0xFF);
    dhcpm->options[pointer++] = (dhcpl.siaddr & 0xFF);
    dhcpm->options[pointer++] = LEASE;
    dhcpm->options[pointer++] = 4;
    dhcpm->options[pointer++] = (dhcpl.lease >> 24);
    dhcpm->options[pointer++] = ((dhcpl.lease >> 16) & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.lease >> 8) & 0xFF);
    dhcpm->options[pointer++] = (dhcpl.lease & 0xFF);
    dhcpm->options[pointer++] = REBINDING;
    dhcpm->options[pointer++] = 4;
    dhcpm->options[pointer++] = (dhcpl.lease >> 24);
    dhcpm->options[pointer++] = ((dhcpl.lease >> 16) & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.lease >> 8) & 0xFF);
    dhcpm->options[pointer++] = (dhcpl.lease & 0xFF);
    dhcpm->options[pointer++] = RENEWALTIME;
    dhcpm->options[pointer++] = 4;
    dhcpm->options[pointer++] = (dhcpl.lease >> 24);
    dhcpm->options[pointer++] = ((dhcpl.lease >> 16) & 0xFF);
    dhcpm->options[pointer++] = ((dhcpl.lease >> 8) & 0xFF);
    dhcpm->options[pointer++] = (dhcpl.lease & 0xFF);
    dhcpm->options[pointer++] = PAD;
    dhcpm->options[pointer++] = PAD;
    dhcpm->options[pointer++] = PAD;
    dhcpm->options[pointer++] = END;
    for( ; pointer < 312; pointer++ )
      dhcpm->options[pointer] = PAD;
    dhcpo->type = DHCPACK;
    sprintf( name, "%u.%u.%u.%u", (dhcpl.ip & 0xFF), ((dhcpl.ip>>8) & 0xFF), ((dhcpl.ip>>16)&0xFF), (dhcpl.ip>>24));
    break;

  default:
    break;
  }
  display_dhcp_packet( dhcpm, dhcpo );
  write_packet( dhcpm, name );
  fprintf( stdout, "process_dhcp_packet [end]!\n");
  free( name );
  return 0;
}