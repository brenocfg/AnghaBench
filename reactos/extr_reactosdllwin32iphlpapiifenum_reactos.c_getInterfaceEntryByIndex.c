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
struct TYPE_6__ {int /*<<< orphan*/  if_info; } ;
struct TYPE_5__ {int /*<<< orphan*/ * wszName; } ;
typedef  TYPE_1__* PMIB_IFROW ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_2__ IFInfo ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_READ_DATA ; 
 size_t MAX_INTERFACE_NAME_LEN ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  closeTcpFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getInterfaceInfoByIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  openTcpFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

DWORD getInterfaceEntryByIndex(DWORD index, PMIB_IFROW entry)
{
    HANDLE tcpFile;
    IFInfo info;
    NTSTATUS status = openTcpFile( &tcpFile, FILE_READ_DATA );

    TRACE("Called.\n");

    if( NT_SUCCESS(status) ) {
        status = getInterfaceInfoByIndex( tcpFile, index, &info );

        if( NT_SUCCESS(status) ) {
            memcpy( &entry->wszName[MAX_INTERFACE_NAME_LEN],
                    &info.if_info,
                    sizeof(info.if_info) );
        }

        closeTcpFile( tcpFile );
    }

    return status;
}