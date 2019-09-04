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
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIDocument ;
typedef  int /*<<< orphan*/  nsIDOMHTMLDocument ;
typedef  int /*<<< orphan*/  JSContext ;

/* Variables and functions */
 int /*<<< orphan*/  IID_nsIDocument ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  content_utils ; 
 int /*<<< orphan*/ * nsIContentUtils_GetContextFromDocument (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nsIDOMHTMLDocument_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDocument_Release (int /*<<< orphan*/ *) ; 

JSContext *get_context_from_document(nsIDOMHTMLDocument *nsdoc)
{
    nsIDocument *doc;
    JSContext *ctx;
    nsresult nsres;

    nsres = nsIDOMHTMLDocument_QueryInterface(nsdoc, &IID_nsIDocument, (void**)&doc);
    assert(nsres == NS_OK);

    ctx = nsIContentUtils_GetContextFromDocument(content_utils, doc);
    nsIDocument_Release(doc);

    TRACE("ret %p\n", ctx);
    return ctx;
}