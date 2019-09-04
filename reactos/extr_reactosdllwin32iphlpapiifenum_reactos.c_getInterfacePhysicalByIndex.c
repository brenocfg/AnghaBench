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
typedef  int /*<<< orphan*/  PDWORD ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IFInfo ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_READ_DATA ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closeTcpFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getInterfaceInfoByIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getInterfacePhysicalFromInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openTcpFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

DWORD getInterfacePhysicalByIndex(DWORD index, PDWORD len, PBYTE addr,
 PDWORD type)
{
    HANDLE tcpFile;
    IFInfo info;
    NTSTATUS status = openTcpFile( &tcpFile, FILE_READ_DATA );

    if( NT_SUCCESS(status) ) {
        status = getInterfaceInfoByIndex( tcpFile, index, &info );
        if( NT_SUCCESS(status) )
            getInterfacePhysicalFromInfo( &info, len, addr, type );
        closeTcpFile( tcpFile );
    }

    return status;
}