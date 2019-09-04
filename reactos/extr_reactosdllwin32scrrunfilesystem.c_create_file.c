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
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
struct file {int ref; TYPE_1__ IFile_iface; int /*<<< orphan*/  classinfo; struct file* path; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ IFile ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_File ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int FILE_ATTRIBUTE_DEVICE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int GetFileAttributesW (struct file*) ; 
 int GetFullPathNameW (int /*<<< orphan*/ ,int,struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  create_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_vtbl ; 
 void* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (struct file*) ; 
 int /*<<< orphan*/  init_classinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT create_file(BSTR path, IFile **file)
{
    struct file *f;
    DWORD len, attrs;

    *file = NULL;

    f = heap_alloc(sizeof(struct file));
    if(!f)
        return E_OUTOFMEMORY;

    f->IFile_iface.lpVtbl = &file_vtbl;
    f->ref = 1;

    len = GetFullPathNameW(path, 0, NULL, NULL);
    if(!len) {
        heap_free(f);
        return E_FAIL;
    }

    f->path = heap_alloc(len*sizeof(WCHAR));
    if(!f->path) {
        heap_free(f);
        return E_OUTOFMEMORY;
    }

    if(!GetFullPathNameW(path, len, f->path, NULL)) {
        heap_free(f->path);
        heap_free(f);
        return E_FAIL;
    }

    attrs = GetFileAttributesW(f->path);
    if(attrs==INVALID_FILE_ATTRIBUTES ||
            (attrs&(FILE_ATTRIBUTE_DIRECTORY|FILE_ATTRIBUTE_DEVICE))) {
        heap_free(f->path);
        heap_free(f);
        return create_error(GetLastError());
    }

    init_classinfo(&CLSID_File, (IUnknown *)&f->IFile_iface, &f->classinfo);
    *file = &f->IFile_iface;
    return S_OK;
}