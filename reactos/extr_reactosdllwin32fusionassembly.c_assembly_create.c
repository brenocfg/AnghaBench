#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ hfile; int /*<<< orphan*/  data; int /*<<< orphan*/  hmap; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ ASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  CreateFileMappingW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_MAP_READ ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MapViewOfFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  assembly_release (TYPE_1__*) ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  parse_clr_metadata (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_pe_header (TYPE_1__*) ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/ ) ; 

HRESULT assembly_create(ASSEMBLY **out, LPCWSTR file)
{
    ASSEMBLY *assembly;
    HRESULT hr;

    *out = NULL;

    if (!(assembly = heap_alloc_zero(sizeof(*assembly)))) return E_OUTOFMEMORY;

    assembly->path = strdupW(file);
    if (!assembly->path)
    {
        hr = E_OUTOFMEMORY;
        goto failed;
    }

    assembly->hfile = CreateFileW(file, GENERIC_READ, FILE_SHARE_READ,
                                  NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (assembly->hfile == INVALID_HANDLE_VALUE)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto failed;
    }

    assembly->hmap = CreateFileMappingW(assembly->hfile, NULL, PAGE_READONLY,
                                        0, 0, NULL);
    if (!assembly->hmap)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto failed;
    }

    assembly->data = MapViewOfFile(assembly->hmap, FILE_MAP_READ, 0, 0, 0);
    if (!assembly->data)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto failed;
    }

    hr = parse_pe_header(assembly);
    if (FAILED(hr)) goto failed;

    hr = parse_clr_metadata(assembly);
    if (FAILED(hr)) goto failed;

    *out = assembly;
    return S_OK;

failed:
    assembly_release(assembly);
    return hr;
}