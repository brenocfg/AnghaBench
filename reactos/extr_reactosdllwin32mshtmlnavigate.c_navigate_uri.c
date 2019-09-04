#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int post_data_len; int /*<<< orphan*/ * post_stream; int /*<<< orphan*/ * headers; int /*<<< orphan*/ * post_data; } ;
typedef  TYPE_6__ request_data_t ;
typedef  int /*<<< orphan*/  nsWineURI ;
typedef  int /*<<< orphan*/  nsISupports ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_17__ {TYPE_4__* inner_window; int /*<<< orphan*/  IHTMLWindow2_iface; } ;
struct TYPE_19__ {TYPE_5__ base; TYPE_2__* doc_obj; } ;
struct TYPE_16__ {TYPE_3__* doc; } ;
struct TYPE_15__ {int /*<<< orphan*/  basedoc; } ;
struct TYPE_13__ {TYPE_7__* window; } ;
struct TYPE_14__ {TYPE_1__ basedoc; int /*<<< orphan*/  doc_object_service; scalar_t__ webbrowser; } ;
typedef  int /*<<< orphan*/  IUri ;
typedef  TYPE_7__ HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/ * BSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BINDING_REFRESH ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IDocObjectService_FireBeforeNavigate2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IHTMLWindow2_get_name (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  LOAD_FLAGS_NONE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  create_doc_uri (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hlink_frame_navigate (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  load_nsuri (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsISupports_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  super_navigate (TYPE_7__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,void*,int) ; 

__attribute__((used)) static HRESULT navigate_uri(HTMLOuterWindow *window, IUri *uri, const WCHAR *display_uri, const request_data_t *request_data,
        DWORD flags)
{
    nsWineURI *nsuri;
    HRESULT hres;

    TRACE("%s\n", debugstr_w(display_uri));

    if(window->doc_obj && window->doc_obj->webbrowser) {
        DWORD post_data_len = request_data ? request_data->post_data_len : 0;
        void *post_data = post_data_len ? request_data->post_data : NULL;
        const WCHAR *headers = request_data ? request_data->headers : NULL;

        if(!(flags & BINDING_REFRESH)) {
            BSTR frame_name = NULL;
            BOOL cancel = FALSE;

            if(window != window->doc_obj->basedoc.window) {
                hres = IHTMLWindow2_get_name(&window->base.IHTMLWindow2_iface, &frame_name);
                if(FAILED(hres))
                    return hres;
            }

            hres = IDocObjectService_FireBeforeNavigate2(window->doc_obj->doc_object_service, NULL, display_uri, 0x40,
                    frame_name, post_data, post_data_len ? post_data_len+1 : 0, headers, TRUE, &cancel);
            SysFreeString(frame_name);
            if(SUCCEEDED(hres) && cancel) {
                TRACE("Navigation canceled\n");
                return S_OK;
            }
        }

        if(window == window->doc_obj->basedoc.window)
            return super_navigate(window, uri, flags, headers, post_data, post_data_len);
    }

    if(window->doc_obj && window == window->doc_obj->basedoc.window) {
        BOOL cancel;

        hres = hlink_frame_navigate(&window->base.inner_window->doc->basedoc, display_uri, NULL, 0, &cancel);
        if(FAILED(hres))
            return hres;

        if(cancel) {
            TRACE("Navigation handled by hlink frame\n");
            return S_OK;
        }
    }

    hres = create_doc_uri(window, uri, &nsuri);
    if(FAILED(hres))
        return hres;

    hres = load_nsuri(window, nsuri, request_data ? request_data->post_stream : NULL, NULL, LOAD_FLAGS_NONE);
    nsISupports_Release((nsISupports*)nsuri);
    return hres;
}