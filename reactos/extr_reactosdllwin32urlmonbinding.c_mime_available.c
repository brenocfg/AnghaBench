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
struct TYPE_3__ {int /*<<< orphan*/  mime; int /*<<< orphan*/  clipboard_format; int /*<<< orphan*/  callback; int /*<<< orphan*/  report_mime; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ Binding ;

/* Variables and functions */
 int /*<<< orphan*/  BINDSTATUS_MIMETYPEAVAILABLE ; 
 int /*<<< orphan*/  IBindStatusCallback_OnProgress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterClipboardFormatW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_strdupW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mime_available(Binding *This, LPCWSTR mime)
{
    heap_free(This->mime);
    This->mime = heap_strdupW(mime);

    if(!This->mime || !This->report_mime)
        return;

    IBindStatusCallback_OnProgress(This->callback, 0, 0, BINDSTATUS_MIMETYPEAVAILABLE, This->mime);

    This->clipboard_format = RegisterClipboardFormatW(This->mime);
}