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
struct list {int /*<<< orphan*/  next; } ;
struct keyitem_pair {int /*<<< orphan*/  item; int /*<<< orphan*/  key; int /*<<< orphan*/  entry; int /*<<< orphan*/  bucket; int /*<<< orphan*/  hash; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; struct list pairs; int /*<<< orphan*/  IDictionary_iface; } ;
typedef  TYPE_1__ dictionary ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDictionary_get_HashVal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  V_I4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantCopyInd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 struct list* get_bucket_head (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct keyitem_pair* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (struct keyitem_pair*) ; 
 int /*<<< orphan*/  list_add_tail (struct list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (struct list*) ; 

__attribute__((used)) static HRESULT add_keyitem_pair(dictionary *dict, VARIANT *key, VARIANT *item)
{
    struct keyitem_pair *pair;
    struct list *head;
    VARIANT hash;
    HRESULT hr;

    hr = IDictionary_get_HashVal(&dict->IDictionary_iface, key, &hash);
    if (FAILED(hr))
        return hr;

    pair = heap_alloc(sizeof(*pair));
    if (!pair)
        return E_OUTOFMEMORY;

    pair->hash = V_I4(&hash);
    VariantInit(&pair->key);
    VariantInit(&pair->item);

    hr = VariantCopyInd(&pair->key, key);
    if (FAILED(hr))
        goto failed;

    hr = VariantCopyInd(&pair->item, item);
    if (FAILED(hr))
        goto failed;

    head = get_bucket_head(dict, pair->hash);
    if (!head->next)
        /* this only happens once per bucket */
        list_init(head);

    /* link to bucket list and to full list */
    list_add_tail(head, &pair->bucket);
    list_add_tail(&dict->pairs, &pair->entry);
    dict->count++;
    return S_OK;

failed:
    VariantClear(&pair->key);
    VariantClear(&pair->item);
    heap_free(pair);
    return hr;
}