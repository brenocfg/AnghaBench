#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const WCHAR ;
struct TYPE_4__ {scalar_t__ (* filter ) (int /*<<< orphan*/  const*,int) ;int /*<<< orphan*/  const* mime; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  const* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* app_octetstreamW ; 
 int /*<<< orphan*/  debugstr_an (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  find_mime_from_url (int /*<<< orphan*/  const*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  is_known_mime_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  is_text_plain_char (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 TYPE_1__* mime_filters ; 
 TYPE_1__* mime_filters_any_pos ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int strlenW (int /*<<< orphan*/  const*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ stub3 (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ stub4 (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ stub5 (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* text_plainW ; 

__attribute__((used)) static HRESULT find_mime_from_buffer(const BYTE *buf, DWORD size, const WCHAR *proposed_mime, const WCHAR *url, WCHAR **ret_mime)
{
    int len, i, any_pos_mime = -1;
    const WCHAR *ret = NULL;

    if(!buf || !size) {
        if(!proposed_mime)
            return E_FAIL;

        len = strlenW(proposed_mime)+1;
        *ret_mime = CoTaskMemAlloc(len*sizeof(WCHAR));
        if(!*ret_mime)
            return E_OUTOFMEMORY;

        memcpy(*ret_mime, proposed_mime, len*sizeof(WCHAR));
        return S_OK;
    }

    if(proposed_mime && (!strcmpW(proposed_mime, app_octetstreamW)
                || !strcmpW(proposed_mime, text_plainW)))
        proposed_mime = NULL;

    if(proposed_mime) {
        ret = proposed_mime;

        for(i=0; i < ARRAY_SIZE(mime_filters_any_pos); i++) {
            if(!strcmpW(proposed_mime, mime_filters_any_pos[i].mime)) {
                any_pos_mime = i;
                for(len=size; len>0; len--) {
                    if(mime_filters_any_pos[i].filter(buf+size-len, len))
                        break;
                }
                if(!len)
                    ret = NULL;
                break;
            }
        }

        if(i == ARRAY_SIZE(mime_filters_any_pos)) {
            for(i=0; i < ARRAY_SIZE(mime_filters); i++) {
                if(!strcmpW(proposed_mime, mime_filters[i].mime)) {
                    if(!mime_filters[i].filter(buf, size))
                        ret = NULL;
                    break;
                }
            }
        }
    }

    /* Looks like a bug in native implementation, html and xml mimes
     * are not looked for if none of them was proposed */
    if(!proposed_mime || any_pos_mime!=-1) {
        for(len=size; !ret && len>0; len--) {
            for(i=0; i<ARRAY_SIZE(mime_filters_any_pos); i++) {
                if(mime_filters_any_pos[i].filter(buf+size-len, len)) {
                    ret = mime_filters_any_pos[i].mime;
                    break;
                }
            }
        }
    }

    i=0;
    while(!ret) {
        if(mime_filters[i].filter(buf, size))
            ret = mime_filters[i].mime;
        i++;
    }

    if(any_pos_mime!=-1 && ret==text_plainW)
        ret = mime_filters_any_pos[any_pos_mime].mime;
    else if(proposed_mime && ret==app_octetstreamW) {
        for(len=size; ret==app_octetstreamW && len>0; len--) {
            if(!is_text_plain_char(buf[size-len]))
                break;
            for(i=0; i<ARRAY_SIZE(mime_filters_any_pos); i++) {
                if(mime_filters_any_pos[i].filter(buf+size-len, len)) {
                    ret = text_plainW;
                    break;
                }
            }
        }

        if(ret == app_octetstreamW)
            ret = proposed_mime;
    }

    if(url && (ret == app_octetstreamW || ret == text_plainW)) {
        WCHAR *url_mime;
        HRESULT hres;

        hres = find_mime_from_url(url, &url_mime);
        if(SUCCEEDED(hres)) {
            if(!is_known_mime_type(url_mime)) {
                *ret_mime = url_mime;
                return hres;
            }
            CoTaskMemFree(url_mime);
        }
    }

    TRACE("found %s for %s\n", debugstr_w(ret), debugstr_an((const char*)buf, min(32, size)));

    len = strlenW(ret)+1;
    *ret_mime = CoTaskMemAlloc(len*sizeof(WCHAR));
    if(!*ret_mime)
        return E_OUTOFMEMORY;

    memcpy(*ret_mime, ret, len*sizeof(WCHAR));
    return S_OK;
}