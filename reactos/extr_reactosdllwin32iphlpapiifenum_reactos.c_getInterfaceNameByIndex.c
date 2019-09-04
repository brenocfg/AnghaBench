#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ if_descr; } ;
struct TYPE_5__ {TYPE_2__ ent; } ;
struct TYPE_7__ {TYPE_1__ if_info; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_3__ IFInfo ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_READ_DATA ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closeTcpFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getInterfaceInfoByIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  openTcpFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

const char *getInterfaceNameByIndex(DWORD index)
{
    IFInfo ifInfo;
    HANDLE tcpFile;
    char *interfaceName = 0, *adapter_name = 0;
    NTSTATUS status = openTcpFile( &tcpFile, FILE_READ_DATA );

    if( NT_SUCCESS(status) ) {
        status = getInterfaceInfoByIndex( tcpFile, index, &ifInfo );

        if( NT_SUCCESS(status) ) {
            adapter_name = (char *)ifInfo.if_info.ent.if_descr;

            interfaceName = HeapAlloc( GetProcessHeap(), 0,
                                       strlen(adapter_name) + 1 );
            if (!interfaceName) return NULL;

            strcpy( interfaceName, adapter_name );
        }

        closeTcpFile( tcpFile );
    }

    return interfaceName;
}