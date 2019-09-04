#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_6__ {int num_cols; TYPE_2__* db; } ;
struct TYPE_5__ {int num_streams; TYPE_1__* streams; int /*<<< orphan*/  strings; } ;
struct TYPE_4__ {int /*<<< orphan*/ * stream; int /*<<< orphan*/  str_index; } ;
typedef  TYPE_3__ MSISTREAMSVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int ERROR_FUNCTION_FAILED ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IStream ; 
 int /*<<< orphan*/  IStream_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int MSI_RecordGetIStream (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  StringNonPersistent ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msi_add_string (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT STREAMS_set_row(struct tagMSIVIEW *view, UINT row, MSIRECORD *rec, UINT mask)
{
    MSISTREAMSVIEW *sv = (MSISTREAMSVIEW *)view;

    TRACE("(%p, %d, %p, %08x)\n", view, row, rec, mask);

    if (row > sv->db->num_streams || mask >= (1 << sv->num_cols))
        return ERROR_INVALID_PARAMETER;

    if (mask & 1)
    {
        const WCHAR *name = MSI_RecordGetString( rec, 1 );

        if (!name) return ERROR_INVALID_PARAMETER;
        sv->db->streams[row].str_index = msi_add_string( sv->db->strings, name, -1, StringNonPersistent );
    }
    if (mask & 2)
    {
        IStream *old, *new;
        HRESULT hr;
        UINT r;

        r = MSI_RecordGetIStream( rec, 2, &new );
        if (r != ERROR_SUCCESS)
            return r;

        old = sv->db->streams[row].stream;
        hr = IStream_QueryInterface( new, &IID_IStream, (void **)&sv->db->streams[row].stream );
        if (FAILED( hr ))
        {
            IStream_Release( new );
            return ERROR_FUNCTION_FAILED;
        }
        if (old) IStream_Release( old );
    }

    return ERROR_SUCCESS;
}