#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_11__ {scalar_t__ log_file; } ;
struct TYPE_10__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIPACKAGE ;
typedef  char* MSIHANDLE ;
typedef  char* LPWSTR ;
typedef  scalar_t__ INT ;
typedef  int INSTALLMESSAGE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int INSTALLMESSAGE_PROGRESS ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ MSI_FormatRecordW (TYPE_2__*,TYPE_1__*,char*,int*) ; 
 int /*<<< orphan*/  MsiCloseHandle (char*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,char*,int,int*,int /*<<< orphan*/ *) ; 
 char* alloc_msihandle (int /*<<< orphan*/ *) ; 
 char* debugstr_a (char*) ; 
 char* debugstr_w (char*) ; 
 int /*<<< orphan*/  dump_record (TYPE_1__*) ; 
 int /*<<< orphan*/  gUIContext ; 
 int /*<<< orphan*/  gUIContextRecord ; 
 int gUIFilter ; 
 int gUIFilterRecord ; 
 scalar_t__ gUIHandlerA (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ gUIHandlerRecord (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ gUIHandlerW (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ internal_ui_handler (TYPE_2__*,int,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msi ; 
 char* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (char*) ; 

INT MSI_ProcessMessageVerbatim(MSIPACKAGE *package, INSTALLMESSAGE eMessageType, MSIRECORD *record)
{
    LPWSTR message = {0};
    DWORD len;
    DWORD log_type = 1 << (eMessageType >> 24);
    UINT res;
    INT rc = 0;
    char *msg;

    TRACE("%x\n", eMessageType);
    if (TRACE_ON(msi)) dump_record(record);

    if (!package || !record)
        message = NULL;
    else {
        res = MSI_FormatRecordW(package, record, message, &len);
        if (res != ERROR_SUCCESS && res != ERROR_MORE_DATA)
            return res;
        len++;
        message = msi_alloc(len * sizeof(WCHAR));
        if (!message) return ERROR_OUTOFMEMORY;
        MSI_FormatRecordW(package, record, message, &len);
    }

    /* convert it to ASCII */
    len = WideCharToMultiByte( CP_ACP, 0, message, -1, NULL, 0, NULL, NULL );
    msg = msi_alloc( len );
    WideCharToMultiByte( CP_ACP, 0, message, -1, msg, len, NULL, NULL );

    if (gUIHandlerRecord && (gUIFilterRecord & log_type))
    {
        MSIHANDLE rec = alloc_msihandle(&record->hdr);
        TRACE("Calling UI handler %p(pvContext=%p, iMessageType=%08x, hRecord=%u)\n",
              gUIHandlerRecord, gUIContextRecord, eMessageType, rec);
        rc = gUIHandlerRecord( gUIContextRecord, eMessageType, rec );
        MsiCloseHandle( rec );
    }
    if (!rc && gUIHandlerW && (gUIFilter & log_type))
    {
        TRACE("Calling UI handler %p(pvContext=%p, iMessageType=%08x, szMessage=%s)\n",
              gUIHandlerW, gUIContext, eMessageType, debugstr_w(message));
        rc = gUIHandlerW( gUIContext, eMessageType, message );
    }
    else if (!rc && gUIHandlerA && (gUIFilter & log_type))
    {
        TRACE("Calling UI handler %p(pvContext=%p, iMessageType=%08x, szMessage=%s)\n",
              gUIHandlerA, gUIContext, eMessageType, debugstr_a(msg));
        rc = gUIHandlerA( gUIContext, eMessageType, msg );
    }

    if (!rc)
        rc = internal_ui_handler(package, eMessageType, record, message);

    if (!rc && package && package->log_file != INVALID_HANDLE_VALUE &&
        (eMessageType & 0xff000000) != INSTALLMESSAGE_PROGRESS)
    {
        DWORD written;
        WriteFile( package->log_file, msg, len - 1, &written, NULL );
        WriteFile( package->log_file, "\n", 1, &written, NULL );
    }
    msi_free( msg );
    msi_free( message );

    return rc;
}