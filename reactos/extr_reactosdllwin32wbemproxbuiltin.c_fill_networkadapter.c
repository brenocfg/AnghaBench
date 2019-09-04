#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct table {scalar_t__ num_rows; scalar_t__ data; } ;
struct record_networkadapter {int physicaladapter; int speed; int /*<<< orphan*/  pnpdevice_id; int /*<<< orphan*/  netconnection_status; void* name; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  mac_address; int /*<<< orphan*/  interface_index; int /*<<< orphan*/  index; void* device_id; int /*<<< orphan*/  adaptertype; } ;
struct expr {int dummy; } ;
typedef  enum fill_status { ____Placeholder_fill_status } fill_status ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  IfIndex; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
struct TYPE_9__ {scalar_t__ IfType; char* FriendlyName; int /*<<< orphan*/  OperStatus; int /*<<< orphan*/  PhysicalAddressLength; int /*<<< orphan*/  PhysicalAddress; TYPE_2__ u; struct TYPE_9__* Next; } ;
typedef  TYPE_3__ IP_ADAPTER_ADDRESSES ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 scalar_t__ ERROR_BUFFER_OVERFLOW ; 
 int FILL_STATUS_FAILED ; 
 int FILL_STATUS_UNFILTERED ; 
 scalar_t__ GetAdaptersAddresses (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,scalar_t__*) ; 
 scalar_t__ IF_TYPE_SOFTWARE_LOOPBACK ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  compsys_manufacturerW ; 
 int /*<<< orphan*/  free_row_values (struct table*,scalar_t__) ; 
 int /*<<< orphan*/  get_adaptertype (scalar_t__,int*) ; 
 int /*<<< orphan*/  get_connection_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mac_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* heap_alloc (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (TYPE_3__*) ; 
 void* heap_strdupW (char*) ; 
 int /*<<< orphan*/  match_row (struct table*,scalar_t__,struct expr const*,int*) ; 
 int /*<<< orphan*/  networkadapter_pnpdeviceidW ; 
 int /*<<< orphan*/  resize_table (struct table*,scalar_t__,int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum fill_status fill_networkadapter( struct table *table, const struct expr *cond )
{
    static const WCHAR fmtW[] = {'%','u',0};
    WCHAR device_id[11];
    struct record_networkadapter *rec;
    IP_ADAPTER_ADDRESSES *aa, *buffer;
    UINT row = 0, offset = 0, count = 0;
    DWORD size = 0, ret;
    int physical;
    enum fill_status status = FILL_STATUS_UNFILTERED;

    ret = GetAdaptersAddresses( AF_UNSPEC, 0, NULL, NULL, &size );
    if (ret != ERROR_BUFFER_OVERFLOW) return FILL_STATUS_FAILED;

    if (!(buffer = heap_alloc( size ))) return FILL_STATUS_FAILED;
    if (GetAdaptersAddresses( AF_UNSPEC, 0, NULL, buffer, &size ))
    {
        heap_free( buffer );
        return FILL_STATUS_FAILED;
    }
    for (aa = buffer; aa; aa = aa->Next)
    {
        if (aa->IfType != IF_TYPE_SOFTWARE_LOOPBACK) count++;
    }
    if (!resize_table( table, count, sizeof(*rec) ))
    {
        heap_free( buffer );
        return FILL_STATUS_FAILED;
    }
    for (aa = buffer; aa; aa = aa->Next)
    {
        if (aa->IfType == IF_TYPE_SOFTWARE_LOOPBACK) continue;

        rec = (struct record_networkadapter *)(table->data + offset);
        sprintfW( device_id, fmtW, aa->u.s.IfIndex );
        rec->adaptertype          = get_adaptertype( aa->IfType, &physical );
        rec->device_id            = heap_strdupW( device_id );
        rec->index                = aa->u.s.IfIndex;
        rec->interface_index      = aa->u.s.IfIndex;
        rec->mac_address          = get_mac_address( aa->PhysicalAddress, aa->PhysicalAddressLength );
        rec->manufacturer         = compsys_manufacturerW;
        rec->name                 = heap_strdupW( aa->FriendlyName );
        rec->netconnection_status = get_connection_status( aa->OperStatus );
        rec->physicaladapter      = physical;
        rec->pnpdevice_id         = networkadapter_pnpdeviceidW;
        rec->speed                = 1000000;
        if (!match_row( table, row, cond, &status ))
        {
            free_row_values( table, row );
            continue;
        }
        offset += sizeof(*rec);
        row++;
    }
    TRACE("created %u rows\n", row);
    table->num_rows = row;

    heap_free( buffer );
    return status;
}