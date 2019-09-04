#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  binding; } ;
struct TYPE_10__ {TYPE_2__ bsc; TYPE_1__* nschannel; int /*<<< orphan*/  is_doc_channel; } ;
typedef  TYPE_3__ nsChannelBSC ;
typedef  int ULONG ;
struct TYPE_8__ {int /*<<< orphan*/  content_type; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IWinInetHttpInfo ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BSCallback ;

/* Variables and functions */
#define  BINDSTATUS_BEGINDOWNLOADDATA 130 
#define  BINDSTATUS_MIMETYPEAVAILABLE 129 
#define  BINDSTATUS_REDIRECTING 128 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int HTTP_QUERY_FLAG_NUMBER ; 
 int HTTP_QUERY_STATUS_CODE ; 
 int HTTP_STATUS_OK ; 
 int /*<<< orphan*/  IBinding_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IWinInetHttpInfo ; 
 int /*<<< orphan*/  IWinInetHttpInfo_QueryInfo (int /*<<< orphan*/ *,int,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWinInetHttpInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_extern_mime_navigation (TYPE_3__*) ; 
 int /*<<< orphan*/  handle_navigation_error (TYPE_3__*,int) ; 
 int /*<<< orphan*/  handle_redirect (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_strdupWtoA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_supported_doc_mime (int /*<<< orphan*/ ) ; 
 TYPE_3__* nsChannelBSC_from_BSCallback (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT nsChannelBSC_on_progress(BSCallback *bsc, ULONG status_code, LPCWSTR status_text)
{
    nsChannelBSC *This = nsChannelBSC_from_BSCallback(bsc);

    switch(status_code) {
    case BINDSTATUS_MIMETYPEAVAILABLE:
        if(This->is_doc_channel && !is_supported_doc_mime(status_text)) {
            FIXME("External MIME: %s\n", debugstr_w(status_text));

            handle_extern_mime_navigation(This);

            This->nschannel = NULL;
        }

        if(!This->nschannel)
            return S_OK;

        heap_free(This->nschannel->content_type);
        This->nschannel->content_type = heap_strdupWtoA(status_text);
        break;
    case BINDSTATUS_REDIRECTING:
        return handle_redirect(This, status_text);
    case BINDSTATUS_BEGINDOWNLOADDATA: {
        IWinInetHttpInfo *http_info;
        DWORD status, size = sizeof(DWORD);
        HRESULT hres;

        if(!This->bsc.binding)
            break;

        hres = IBinding_QueryInterface(This->bsc.binding, &IID_IWinInetHttpInfo, (void**)&http_info);
        if(FAILED(hres))
            break;

        hres = IWinInetHttpInfo_QueryInfo(http_info,
                HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER, &status, &size, NULL, NULL);
        IWinInetHttpInfo_Release(http_info);
        if(FAILED(hres) || status == HTTP_STATUS_OK)
            break;

        handle_navigation_error(This, status);
    }
    }

    return S_OK;
}