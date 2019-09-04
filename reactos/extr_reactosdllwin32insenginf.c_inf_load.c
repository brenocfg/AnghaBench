#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inf_file {int size; void* content; int /*<<< orphan*/  sections; } ;
struct TYPE_3__ {int QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetFileSizeEx (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  ReadFile (scalar_t__,void*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 void* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  inf_free (struct inf_file*) ; 
 int /*<<< orphan*/  inf_process_content (struct inf_file*) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

HRESULT inf_load(const char *path, struct inf_file **inf_file)
{
    LARGE_INTEGER file_size;
    struct inf_file *inf;
    HRESULT hr = E_FAIL;
    HANDLE file;
    DWORD read;

    file = CreateFileA(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) return E_FAIL;

    inf = heap_alloc_zero(sizeof(*inf));
    if (!inf) goto error;

    if (!GetFileSizeEx(file, &file_size))
        goto error;

    inf->size = file_size.QuadPart;

    inf->content = heap_alloc_zero(inf->size);
    if (!inf->content) goto error;

    list_init(&inf->sections);

    if (!ReadFile(file, inf->content, inf->size, &read, NULL) || read != inf->size)
        goto error;

    hr = inf_process_content(inf);
    if (FAILED(hr)) goto error;

    CloseHandle(file);
    *inf_file = inf;
    return S_OK;

error:
    if (inf) inf_free(inf);
    CloseHandle(file);
    return hr;
}