#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct table {size_t data; size_t num_rows; } ;
struct record_service {int accept_pause; int accept_stop; int /*<<< orphan*/  stop_service; int /*<<< orphan*/  start_service; int /*<<< orphan*/  resume_service; int /*<<< orphan*/  pause_service; void* systemname; int /*<<< orphan*/  state; int /*<<< orphan*/  startmode; int /*<<< orphan*/  servicetype; int /*<<< orphan*/  process_id; void* name; void* displayname; } ;
struct expr {int dummy; } ;
typedef  enum fill_status { ____Placeholder_fill_status } fill_status ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_9__ {int dwControlsAccepted; int /*<<< orphan*/  dwCurrentState; int /*<<< orphan*/  dwServiceType; int /*<<< orphan*/  dwProcessId; } ;
struct TYPE_10__ {int /*<<< orphan*/  dwStartType; int /*<<< orphan*/ * lpServiceName; int /*<<< orphan*/ * lpDisplayName; TYPE_1__ ServiceStatusProcess; } ;
typedef  TYPE_1__ SERVICE_STATUS_PROCESS ;
typedef  int /*<<< orphan*/  SC_HANDLE ;
typedef  TYPE_2__ QUERY_SERVICE_CONFIGW ;
typedef  TYPE_2__ ENUM_SERVICE_STATUS_PROCESSW ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ EnumServicesStatusExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,size_t*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FILL_STATUS_FAILED ; 
 int FILL_STATUS_UNFILTERED ; 
 int /*<<< orphan*/  GetComputerNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  MAX_COMPUTERNAME_LENGTH ; 
 int /*<<< orphan*/  OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_ENUM_PROCESS_INFO ; 
 int /*<<< orphan*/  SC_MANAGER_ENUMERATE_SERVICE ; 
 int SERVICE_ACCEPT_PAUSE_CONTINUE ; 
 int SERVICE_ACCEPT_STOP ; 
 int /*<<< orphan*/  SERVICE_STATE_ALL ; 
 int /*<<< orphan*/  SERVICE_TYPE_ALL ; 
 int /*<<< orphan*/  TRACE (char*,size_t) ; 
 int /*<<< orphan*/  free_row_values (struct table*,size_t) ; 
 int /*<<< orphan*/  get_service_startmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_service_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_service_type (int /*<<< orphan*/ ) ; 
 TYPE_2__* heap_alloc (size_t) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 TYPE_2__* heap_realloc (TYPE_2__*,size_t) ; 
 void* heap_strdupW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  match_row (struct table*,size_t,struct expr const*,int*) ; 
 TYPE_2__* query_service_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resize_table (struct table*,size_t,int) ; 
 int /*<<< orphan*/  service_pause_service ; 
 int /*<<< orphan*/  service_resume_service ; 
 int /*<<< orphan*/  service_start_service ; 
 int /*<<< orphan*/  service_stop_service ; 

__attribute__((used)) static enum fill_status fill_service( struct table *table, const struct expr *cond )
{
    struct record_service *rec;
    SC_HANDLE manager;
    ENUM_SERVICE_STATUS_PROCESSW *tmp, *services = NULL;
    SERVICE_STATUS_PROCESS *status;
    WCHAR sysnameW[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD len = ARRAY_SIZE( sysnameW );
    UINT i, row = 0, offset = 0, size = 256, needed, count;
    enum fill_status fill_status = FILL_STATUS_FAILED;
    BOOL ret;

    if (!(manager = OpenSCManagerW( NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE ))) return FILL_STATUS_FAILED;
    if (!(services = heap_alloc( size ))) goto done;

    ret = EnumServicesStatusExW( manager, SC_ENUM_PROCESS_INFO, SERVICE_TYPE_ALL,
                                 SERVICE_STATE_ALL, (BYTE *)services, size, &needed,
                                 &count, NULL, NULL );
    if (!ret)
    {
        if (GetLastError() != ERROR_MORE_DATA) goto done;
        size = needed;
        if (!(tmp = heap_realloc( services, size ))) goto done;
        services = tmp;
        ret = EnumServicesStatusExW( manager, SC_ENUM_PROCESS_INFO, SERVICE_TYPE_ALL,
                                     SERVICE_STATE_ALL, (BYTE *)services, size, &needed,
                                     &count, NULL, NULL );
        if (!ret) goto done;
    }
    if (!resize_table( table, count, sizeof(*rec) )) goto done;

    GetComputerNameW( sysnameW, &len );
    fill_status = FILL_STATUS_UNFILTERED;

    for (i = 0; i < count; i++)
    {
        QUERY_SERVICE_CONFIGW *config;

        if (!(config = query_service_config( manager, services[i].lpServiceName ))) continue;

        status = &services[i].ServiceStatusProcess;
        rec = (struct record_service *)(table->data + offset);
        rec->accept_pause   = (status->dwControlsAccepted & SERVICE_ACCEPT_PAUSE_CONTINUE) ? -1 : 0;
        rec->accept_stop    = (status->dwControlsAccepted & SERVICE_ACCEPT_STOP) ? -1 : 0;
        rec->displayname    = heap_strdupW( services[i].lpDisplayName );
        rec->name           = heap_strdupW( services[i].lpServiceName );
        rec->process_id     = status->dwProcessId;
        rec->servicetype    = get_service_type( status->dwServiceType );
        rec->startmode      = get_service_startmode( config->dwStartType );
        rec->state          = get_service_state( status->dwCurrentState );
        rec->systemname     = heap_strdupW( sysnameW );
        rec->pause_service  = service_pause_service;
        rec->resume_service = service_resume_service;
        rec->start_service  = service_start_service;
        rec->stop_service   = service_stop_service;
        heap_free( config );
        if (!match_row( table, row, cond, &fill_status ))
        {
            free_row_values( table, row );
            continue;
        }
        offset += sizeof(*rec);
        row++;
    }

    TRACE("created %u rows\n", row);
    table->num_rows = row;

done:
    CloseServiceHandle( manager );
    heap_free( services );
    return fill_status;
}