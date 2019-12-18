#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* options; } ;
struct TYPE_5__ {int type; int r_ip; int r_mask; int r_router; int r_lease; char* hostname; } ;
typedef  TYPE_1__ DHCPOPTIONS ;
typedef  TYPE_2__ DHCPMESSAGE ;

/* Variables and functions */
#define  ALLSUBLOCAL 203 
#define  ARPCACHE 202 
#define  BOOTFILE 201 
#define  BOOTFILESIZE 200 
#define  BROADCAST 199 
#define  CLIENT 198 
#define  COOKIESERVER 197 
#define  DEFAULTTTL 196 
#define  DNS 195 
#define  DOMAINNAME 194 
#define  END 193 
#define  ETHENCAPSUL 192 
#define  EXTENSIONPATH 191 
#define  FINGERSERVER 190 
#define  HOSTNAME 189 
#define  HTTPSERVER 188 
#define  IMPSERVER 187 
#define  IMTU 186 
#define  IP 185 
#define  IPFORWARD 184 
#define  IRCSERVER 183 
#define  LEASE 182 
#define  LOGSERVER 181 
#define  LPRSERVER 180 
#define  MASK 179 
#define  MASKSUPPLIER 178 
#define  MAXIMUMDATAG 177 
#define  MAXIMUMDHCP 176 
#define  MERITDUMPFILE 175 
#define  MESSAGE 174 
#define  MESSAGETYPE 173 
#define  MOBILEIP 172 
#define  NBTCPIPDDS 171 
#define  NBTCPIPNS 170 
#define  NBTCPIPNT 169 
#define  NBTCPIPSC 168 
#define  NISDOMAIN 167 
#define  NISPLUSDOMAIN 166 
#define  NISPLUSSERVER 165 
#define  NISSERVER 164 
#define  NNTPSERVER 163 
#define  NONLOCAL 162 
#define  NS 161 
#define  NTPSERVER 160 
#define  OVERLOAD 159 
#define  PAD 158 
#define  PATHMTUATO 157 
#define  PATHMTUPTO 156 
#define  PMASKDISCOVERY 155 
#define  POLICYFILTER 154 
#define  POP3SERVER 153 
#define  PREQUEST 152 
#define  PROUTERDISCOVE 151 
#define  REBINDING 150 
#define  RENEWALTIME 149 
#define  RESLOCSERVER 148 
#define  ROOTPATH 147 
#define  ROUTER 146 
#define  RSOLICIADDRESS 145 
#define  SERVER 144 
#define  SMTPSERVER 143 
#define  STATICROUTE 142 
#define  STREETTALKDA 141 
#define  STREETTALKSE 140 
#define  SWAPSERVER 139 
#define  TCPDEFTTL 138 
#define  TCPKAG 137 
#define  TCPKAI 136 
#define  TENCAPSULATION 135 
#define  TFTPSERVER 134 
#define  TIMESERVER 133 
#define  TOFFSET 132 
#define  VENDORCLASS 131 
#define  VENDORSP 130 
#define  XWINDISPLAY 129 
#define  XWINFONTSERVER 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strncpy (char*,int*,int) ; 

int parse_dhcp_options( DHCPMESSAGE *dhcpm, DHCPOPTIONS *dhcpo )
{
  int pointer, opointer;
  int olength;

  pointer = 0;

  fprintf( stdout, "parse_dhcp_options [begin]!\n");

  /* Options Initialization */
  /* No message type */
  dhcpo->type = 0;
  /* No ip address, 0.0.0.0 */
  dhcpo->r_ip = 0;
  /* No mask address, 0.0.0.0 */
  dhcpo->r_mask = 0;
  /* No router, 0.0.0.0 */
  dhcpo->r_router = 0;
  /* No lease 0 */
  dhcpo->r_lease = 0;
  /* No name '\n' */
  dhcpo->hostname = NULL;

  while( pointer< 312 )
    {
      if(( dhcpm->options[0] != 99 ) && (dhcpm->options[1]!=130) && (dhcpm->options[2]!=83) && (dhcpm->options[3]!= 99))
	{
	  fprintf( stdout, "No magic cookie! Aborting! \n" );
	  return -1;
	}
      switch( dhcpm->options[pointer] ){
      case PAD:
	pointer++;
	break;
      case MESSAGETYPE:
	/* Try to figure out the kind of message and start the configuring process */
	pointer += 2;
	dhcpo->type = dhcpm->options[pointer++];
	break;
      case PREQUEST:
	/* Take note of the requested parameters */
	opointer = pointer + 2;
	olength = pointer + dhcpm->options[pointer + 1];
	while( opointer < olength )
	  {
	    switch( dhcpm->options[opointer] ){
	    case IP:
	      /* Take note of the requested ip */
	      opointer += 2;
	      dhcpo->r_ip += dhcpm->options[opointer++];
	      dhcpo->r_ip = dhcpo->r_ip << 8;
	      dhcpo->r_ip += dhcpm->options[opointer++];
	      dhcpo->r_ip = dhcpo->r_ip << 8;
	      dhcpo->r_ip += dhcpm->options[opointer++];
	      dhcpo->r_ip = dhcpo->r_ip << 8;
	      dhcpo->r_ip += dhcpm->options[opointer++];
	      break;
	    case MASK:
	      /* Take note of the requested mask */
	      opointer += 2;
	      dhcpo->r_mask += dhcpm->options[opointer++];
	      dhcpo->r_mask = dhcpo->r_ip << 8;
	      dhcpo->r_mask += dhcpm->options[opointer++];
	      dhcpo->r_mask = dhcpo->r_ip << 8;
	      dhcpo->r_mask += dhcpm->options[opointer++];
	      dhcpo->r_mask = dhcpo->r_ip << 8;
	      dhcpo->r_mask += dhcpm->options[opointer++];
	      break;
	    case ROUTER:
	      /* Take note of the requested router */
	      opointer += 2;
	      dhcpo->r_router += dhcpm->options[opointer++];
	      dhcpo->r_router = dhcpo->r_ip << 8;
	      dhcpo->r_router += dhcpm->options[opointer++];
	      dhcpo->r_router = dhcpo->r_ip << 8;
	      dhcpo->r_router += dhcpm->options[opointer++];
	      dhcpo->r_router = dhcpo->r_ip << 8;
	      dhcpo->r_router += dhcpm->options[opointer++];
	      break;
	    case LEASE:
	      opointer += 2;
	      dhcpo->r_lease += dhcpm->options[opointer++];
	      dhcpo->r_lease = dhcpo->r_ip << 8;
	      dhcpo->r_lease += dhcpm->options[opointer++];
	      dhcpo->r_lease = dhcpo->r_ip << 8;
	      dhcpo->r_lease += dhcpm->options[opointer++];
	      dhcpo->r_lease = dhcpo->r_ip << 8;
	      dhcpo->r_lease += dhcpm->options[opointer++];
	      break;
	    case HOSTNAME:
	      opointer += 1;
	      dhcpo->hostname = (char *)malloc( dhcpm->options[opointer] + 1);
	      strncpy( dhcpo->hostname, &dhcpm->options[opointer+1], dhcpm->options[opointer] );
	      opointer += dhcpm->options[opointer] + 1;
	    default:
	      /* Ignore option */
	      opointer++;
	      break;
	    }
	  }
	pointer = opointer;
	break;
      case  TOFFSET:
      case  TIMESERVER:
      case  NS:
      case  DNS:
      case  LOGSERVER:
      case  COOKIESERVER:
      case  LPRSERVER:
      case  IMPSERVER:
      case  RESLOCSERVER:
      case  BOOTFILESIZE:
      case  MERITDUMPFILE:
      case  DOMAINNAME:
      case  SWAPSERVER:
      case  ROOTPATH:
      case  EXTENSIONPATH:
      case  IPFORWARD:
      case  NONLOCAL:
      case  POLICYFILTER:
      case  MAXIMUMDATAG:
      case  DEFAULTTTL:
      case  PATHMTUATO:
      case  PATHMTUPTO:
      case  IMTU:
      case  ALLSUBLOCAL:
      case  BROADCAST:
      case  PMASKDISCOVERY:
      case  MASKSUPPLIER:
      case  PROUTERDISCOVE:
      case  RSOLICIADDRESS:
      case  STATICROUTE:
      case  TENCAPSULATION:
      case  ARPCACHE:
      case  ETHENCAPSUL:
      case  TCPDEFTTL:
      case  TCPKAI:
      case  TCPKAG:
      case  NISDOMAIN:
      case  NISSERVER:
      case  NTPSERVER:
      case  VENDORSP:
      case  NBTCPIPNS:
      case  NBTCPIPDDS:
      case  NBTCPIPNT:
      case  NBTCPIPSC:
      case  XWINFONTSERVER:
      case  XWINDISPLAY:
      case  OVERLOAD:
      case  SERVER:
      case  MESSAGE:
      case  MAXIMUMDHCP:
      case  RENEWALTIME:
      case  REBINDING:
      case  VENDORCLASS:
      case  NISPLUSDOMAIN:
      case  NISPLUSSERVER:
      case  TFTPSERVER:
      case  BOOTFILE:
      case  MOBILEIP:
      case  SMTPSERVER:
      case  POP3SERVER:
      case  NNTPSERVER:
      case  HTTPSERVER:
      case  FINGERSERVER:
      case  IRCSERVER:
      case  STREETTALKSE:
      case  STREETTALKDA:
      case CLIENT:
	pointer++;
	pointer += dhcpm->options[pointer];
      case END:
	/* return to the calling functions because this is over */
	fprintf( stdout, "parse_dhcp_options: END option found! [end]!\n");
	return 0;
      default:
	/* ignored */
	pointer++;
	break;
      }
    }
  fprintf( stdout, "parse_dhcp_options [end]!\n");
  return 0;
}