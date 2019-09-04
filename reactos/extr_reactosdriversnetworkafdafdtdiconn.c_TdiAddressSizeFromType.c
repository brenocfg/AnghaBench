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
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,int) ; 
 int TDI_ADDRESS_LENGTH_APPLETALK ; 
 int TDI_ADDRESS_LENGTH_IP ; 
 int TDI_ADDRESS_LENGTH_IPX ; 
 int TDI_ADDRESS_LENGTH_NETBIOS ; 
 int TDI_ADDRESS_LENGTH_VNS ; 
#define  TDI_ADDRESS_TYPE_APPLETALK 132 
#define  TDI_ADDRESS_TYPE_IP 131 
#define  TDI_ADDRESS_TYPE_IPX 130 
#define  TDI_ADDRESS_TYPE_NETBIOS 129 
#define  TDI_ADDRESS_TYPE_VNS 128 

UINT TdiAddressSizeFromType( UINT AddressType ) {
    switch( AddressType ) {
    case TDI_ADDRESS_TYPE_IP:
        return TDI_ADDRESS_LENGTH_IP;
    case TDI_ADDRESS_TYPE_APPLETALK:
        return TDI_ADDRESS_LENGTH_APPLETALK;
    case TDI_ADDRESS_TYPE_NETBIOS:
        return TDI_ADDRESS_LENGTH_NETBIOS;
    /* case TDI_ADDRESS_TYPE_NS: */
    case TDI_ADDRESS_TYPE_IPX:
        return TDI_ADDRESS_LENGTH_IPX;
    case TDI_ADDRESS_TYPE_VNS:
        return TDI_ADDRESS_LENGTH_VNS;
    default:
        DbgPrint("TdiAddressSizeFromType - invalid type: %x\n", AddressType);
        return 0;
    }
}