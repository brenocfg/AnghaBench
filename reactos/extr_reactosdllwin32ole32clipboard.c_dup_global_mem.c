#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HGLOBAL ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/ * GlobalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* GlobalLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT dup_global_mem( HGLOBAL src, DWORD flags, HGLOBAL *dst )
{
    void *src_ptr, *dst_ptr;
    DWORD size;

    *dst = NULL;
    if ( !src ) return S_FALSE;

    size = GlobalSize(src);

    *dst = GlobalAlloc( flags, size );
    if ( !*dst ) return E_OUTOFMEMORY;

    src_ptr = GlobalLock(src);
    dst_ptr = GlobalLock(*dst);

    memcpy(dst_ptr, src_ptr, size);

    GlobalUnlock(*dst);
    GlobalUnlock(src);

    return S_OK;
}