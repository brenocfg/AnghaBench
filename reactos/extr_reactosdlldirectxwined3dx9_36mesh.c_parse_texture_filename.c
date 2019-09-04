#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  filename_in ;
struct TYPE_9__ {TYPE_1__* lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* Unlock ) (TYPE_2__*) ;int /*<<< orphan*/  (* Lock ) (TYPE_2__*,int*,void const**) ;} ;
typedef  int SIZE_T ;
typedef  TYPE_2__ ID3DXFileData ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int*,void const**) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*) ; 

__attribute__((used)) static HRESULT parse_texture_filename(ID3DXFileData *filedata, char **filename_out)
{
    HRESULT hr;
    SIZE_T data_size;
    BYTE *data;
    char *filename_in;
    char *filename = NULL;

    /* template TextureFilename {
     *     STRING filename;
     * }
     */

    HeapFree(GetProcessHeap(), 0, *filename_out);
    *filename_out = NULL;

    hr = filedata->lpVtbl->Lock(filedata, &data_size, (const void**)&data);
    if (FAILED(hr)) return hr;

    /* FIXME: String must be retrieved directly instead of through a pointer once ID3DXFILE is fixed */
    if (data_size < sizeof(filename_in))
    {
        WARN("truncated data (%lu bytes)\n", data_size);
        filedata->lpVtbl->Unlock(filedata);
        return E_FAIL;
    }
    filename_in = *(char **)data;

    filename = HeapAlloc(GetProcessHeap(), 0, strlen(filename_in) + 1);
    if (!filename) {
        filedata->lpVtbl->Unlock(filedata);
        return E_OUTOFMEMORY;
    }

    strcpy(filename, filename_in);
    *filename_out = filename;

    filedata->lpVtbl->Unlock(filedata);

    return D3D_OK;
}