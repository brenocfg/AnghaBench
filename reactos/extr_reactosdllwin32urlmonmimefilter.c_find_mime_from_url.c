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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  find_mime_from_ext (char*,char**) ; 
 char* heap_alloc (unsigned int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 

__attribute__((used)) static HRESULT find_mime_from_url(const WCHAR *url, WCHAR **ret)
{
    const WCHAR *ptr, *end_ptr;
    WCHAR *ext = NULL;
    HRESULT hres;

    for(end_ptr = url; *end_ptr; end_ptr++) {
        if(*end_ptr == '?' || *end_ptr == '#')
            break;
    }

    for(ptr = end_ptr; ptr >= url; ptr--) {
        if(*ptr == '.')
            break;
    }

    if(ptr < url)
        return E_FAIL;

    if(*end_ptr) {
        unsigned len = end_ptr-ptr;

        ext = heap_alloc((len+1)*sizeof(WCHAR));
        if(!ext)
            return E_OUTOFMEMORY;

        memcpy(ext, ptr, len*sizeof(WCHAR));
        ext[len] = 0;
    }

    hres = find_mime_from_ext(ext ? ext : ptr, ret);
    heap_free(ext);
    return hres;
}