#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct list {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  entry; struct TYPE_11__* data; struct TYPE_11__* header; } ;
typedef  TYPE_1__ http_header_t ;
typedef  TYPE_1__ WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_wn (TYPE_1__ const*,int) ; 
 TYPE_1__* find_http_header (struct list*,TYPE_1__ const*,int) ; 
 TYPE_1__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 void* heap_strndupW (TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  list_add_tail (struct list*,int /*<<< orphan*/ *) ; 

HRESULT set_http_header(struct list *headers, const WCHAR *name, int name_len,
        const WCHAR *value, int value_len)
{
    http_header_t *header;

    TRACE("%s: %s\n", debugstr_wn(name, name_len), debugstr_wn(value, value_len));

    header = find_http_header(headers, name, name_len);
    if(header) {
        WCHAR *new_data;

        new_data = heap_strndupW(value, value_len);
        if(!new_data)
            return E_OUTOFMEMORY;

        heap_free(header->data);
        header->data = new_data;
    }else {
        header = heap_alloc(sizeof(http_header_t));
        if(!header)
            return E_OUTOFMEMORY;

        header->header = heap_strndupW(name, name_len);
        header->data = heap_strndupW(value, value_len);
        if(!header->header || !header->data) {
            heap_free(header->header);
            heap_free(header->data);
            heap_free(header);
            return E_OUTOFMEMORY;
        }

        list_add_tail(headers, &header->entry);
    }

    return S_OK;
}