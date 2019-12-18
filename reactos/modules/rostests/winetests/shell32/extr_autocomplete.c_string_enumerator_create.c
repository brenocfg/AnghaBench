#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct string_enumerator {int ref; int data_len; TYPE_1__ IEnumString_iface; scalar_t__ cur; int /*<<< orphan*/ ** data; TYPE_2__ IACList_iface; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  aclist_vtbl ; 
 struct string_enumerator* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  string_enumerator_vtbl ; 

__attribute__((used)) static HRESULT string_enumerator_create(void **ppv, WCHAR **suggestions, int count)
{
    struct string_enumerator *object;

    object = heap_alloc_zero(sizeof(*object));
    object->IEnumString_iface.lpVtbl = &string_enumerator_vtbl;
    object->IACList_iface.lpVtbl = &aclist_vtbl;
    object->ref = 1;
    object->data = suggestions;
    object->data_len = count;
    object->cur = 0;

    *ppv = &object->IEnumString_iface;

    return S_OK;
}