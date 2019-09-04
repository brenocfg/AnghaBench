#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ns; int /*<<< orphan*/  nsdef; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
struct ns {int /*<<< orphan*/  entry; int /*<<< orphan*/ * element; int /*<<< orphan*/  prefix; int /*<<< orphan*/  uri; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct ns* reader_alloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  reader_free (TYPE_1__*,struct ns*) ; 
 int /*<<< orphan*/  reader_free_strvalued (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_strvaldup (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT reader_push_ns(xmlreader *reader, const strval *prefix, const strval *uri, BOOL def)
{
    struct ns *ns;
    HRESULT hr;

    ns = reader_alloc(reader, sizeof(*ns));
    if (!ns) return E_OUTOFMEMORY;

    if (def)
        memset(&ns->prefix, 0, sizeof(ns->prefix));
    else {
        hr = reader_strvaldup(reader, prefix, &ns->prefix);
        if (FAILED(hr)) {
            reader_free(reader, ns);
            return hr;
        }
    }

    hr = reader_strvaldup(reader, uri, &ns->uri);
    if (FAILED(hr)) {
        reader_free_strvalued(reader, &ns->prefix);
        reader_free(reader, ns);
        return hr;
    }

    ns->element = NULL;
    list_add_head(def ? &reader->nsdef : &reader->ns, &ns->entry);
    return hr;
}