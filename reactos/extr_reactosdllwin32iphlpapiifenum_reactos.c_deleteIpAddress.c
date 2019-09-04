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
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FILE_READ_DATA ; 
 int FILE_WRITE_DATA ; 
 int /*<<< orphan*/  IOCTL_DELETE_IP_ADDRESS ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtDeviceIoControlFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  closeTcpFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openTcpFile (int /*<<< orphan*/ *,int) ; 

NTSTATUS deleteIpAddress( ULONG NteContext )
{
  HANDLE tcpFile;
  NTSTATUS status = openTcpFile( &tcpFile, FILE_READ_DATA | FILE_WRITE_DATA );
  IO_STATUS_BLOCK Iosb;

  TRACE("Called.\n");

  if( !NT_SUCCESS(status) ) return status;

  status = NtDeviceIoControlFile( tcpFile,
                                  NULL,
                                  NULL,
                                  NULL,
                                  &Iosb,
                                  IOCTL_DELETE_IP_ADDRESS,
                                  &NteContext,
                                  sizeof(USHORT),
                                  NULL,
                                  0 );

  closeTcpFile( tcpFile );

  if (!NT_SUCCESS(status)) {
      ERR("deleteIpAddress(%lu) returning 0x%lx\n", NteContext, status);
  }

  return status;
}