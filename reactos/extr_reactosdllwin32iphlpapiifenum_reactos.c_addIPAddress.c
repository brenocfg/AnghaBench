#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  Information; } ;
struct TYPE_6__ {int /*<<< orphan*/  NewAddress; int /*<<< orphan*/  NewNetmask; int /*<<< orphan*/  NteContext; } ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ IP_SET_DATA ;
typedef  int /*<<< orphan*/  IPMask ;
typedef  int /*<<< orphan*/  IPAddr ;
typedef  TYPE_2__ IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  Data ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FILE_READ_DATA ; 
 int FILE_WRITE_DATA ; 
 int /*<<< orphan*/  IOCTL_SET_IP_ADDRESS ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtDeviceIoControlFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  closeTcpFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openTcpFile (int /*<<< orphan*/ *,int) ; 

NTSTATUS addIPAddress( IPAddr Address, IPMask Mask, DWORD IfIndex,
                       PULONG NteContext, PULONG NteInstance )
{
  HANDLE tcpFile;
  NTSTATUS status = openTcpFile( &tcpFile, FILE_READ_DATA | FILE_WRITE_DATA );
  IP_SET_DATA Data;
  IO_STATUS_BLOCK Iosb;

  TRACE("Called.\n");

  if( !NT_SUCCESS(status) ) return status;

  Data.NteContext = IfIndex;
  Data.NewAddress = Address;
  Data.NewNetmask = Mask;

  status = NtDeviceIoControlFile( tcpFile,
                                  NULL,
                                  NULL,
                                  NULL,
                                  &Iosb,
                                  IOCTL_SET_IP_ADDRESS,
                                  &Data,
                                  sizeof(Data),
                                  &Data,
                                  sizeof(Data) );

  closeTcpFile( tcpFile );

  if( NT_SUCCESS(status) ) {
      *NteContext = Iosb.Information;
      *NteInstance = Data.NewAddress;
  }

  if (!NT_SUCCESS(status)) {
      ERR("addIPAddress for if %d returning 0x%lx\n", IfIndex, status);
  }

  return status;

}