#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIRequest ;
struct TYPE_10__ {int readed; int bom; scalar_t__ binding; } ;
struct TYPE_9__ {TYPE_7__* nsstream; TYPE_4__ bsc; int /*<<< orphan*/  nscontext; TYPE_1__* nschannel; int /*<<< orphan*/  nslistener; scalar_t__ is_doc_channel; scalar_t__ response_processed; } ;
typedef  TYPE_2__ nsChannelBSC ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {int buf_size; int /*<<< orphan*/  nsIInputStream_iface; int /*<<< orphan*/ * buf; } ;
struct TYPE_8__ {int /*<<< orphan*/  nsIHttpChannel_iface; int /*<<< orphan*/  content_type; void* charset; } ;
typedef  int /*<<< orphan*/  IWinInetHttpInfo ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
#define  BOM_NONE 130 
#define  BOM_UTF16 129 
#define  BOM_UTF8 128 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ FindMimeFromData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ IBinding_QueryInterface (scalar_t__,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IWinInetHttpInfo ; 
 int /*<<< orphan*/  IWinInetHttpInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UTF16_STR ; 
 int /*<<< orphan*/  UTF8_STR ; 
 TYPE_7__* create_nsprotocol_stream () ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 void* heap_strdupA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_strdupWtoA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIStreamListener_OnDataAvailable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ on_start_nsrequest (TYPE_2__*) ; 
 int /*<<< orphan*/  query_http_info (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ read_stream (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * text_htmlW ; 

__attribute__((used)) static HRESULT read_stream_data(nsChannelBSC *This, IStream *stream)
{
    DWORD read;
    nsresult nsres;
    HRESULT hres;

    if(!This->response_processed) {
        IWinInetHttpInfo *wininet_info;

        This->response_processed = TRUE;
        if(This->bsc.binding) {
            hres = IBinding_QueryInterface(This->bsc.binding, &IID_IWinInetHttpInfo, (void**)&wininet_info);
            if(SUCCEEDED(hres)) {
                query_http_info(This, wininet_info);
                IWinInetHttpInfo_Release(wininet_info);
            }
        }
    }

    if(!This->nschannel)
        return S_OK;

    if(!This->nslistener) {
        BYTE buf[1024];

        do {
            hres = read_stream(&This->bsc, stream, buf, sizeof(buf), &read);
        }while(hres == S_OK && read);

        return S_OK;
    }

    if(!This->nsstream) {
        This->nsstream = create_nsprotocol_stream();
        if(!This->nsstream)
            return E_OUTOFMEMORY;
    }

    do {
        BOOL first_read = !This->bsc.readed;

        hres = read_stream(&This->bsc, stream, This->nsstream->buf+This->nsstream->buf_size,
                sizeof(This->nsstream->buf)-This->nsstream->buf_size, &read);
        if(!read)
            break;

        This->nsstream->buf_size += read;

        if(first_read) {
            switch(This->bsc.bom) {
            case BOM_UTF8:
                This->nschannel->charset = heap_strdupA(UTF8_STR);
                break;
            case BOM_UTF16:
                This->nschannel->charset = heap_strdupA(UTF16_STR);
            case BOM_NONE:
                /* FIXME: Get charset from HTTP headers */;
            }

            if(!This->nschannel->content_type) {
                WCHAR *mime;

                hres = FindMimeFromData(NULL, NULL, This->nsstream->buf, This->nsstream->buf_size,
                        This->is_doc_channel ? text_htmlW : NULL, 0, &mime, 0);
                if(FAILED(hres))
                    return hres;

                TRACE("Found MIME %s\n", debugstr_w(mime));

                This->nschannel->content_type = heap_strdupWtoA(mime);
                CoTaskMemFree(mime);
                if(!This->nschannel->content_type)
                    return E_OUTOFMEMORY;
            }

            hres = on_start_nsrequest(This);
            if(FAILED(hres))
                return hres;
        }

        nsres = nsIStreamListener_OnDataAvailable(This->nslistener,
                (nsIRequest*)&This->nschannel->nsIHttpChannel_iface, This->nscontext,
                &This->nsstream->nsIInputStream_iface, This->bsc.readed-This->nsstream->buf_size,
                This->nsstream->buf_size);
        if(NS_FAILED(nsres))
            ERR("OnDataAvailable failed: %08x\n", nsres);

        if(This->nsstream->buf_size == sizeof(This->nsstream->buf)) {
            ERR("buffer is full\n");
            break;
        }
    }while(hres == S_OK);

    return S_OK;
}