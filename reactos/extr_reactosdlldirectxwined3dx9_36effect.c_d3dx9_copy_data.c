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
struct d3dx_object {int size; int /*<<< orphan*/ * data; } ;
struct d3dx9_base_effect {struct d3dx_object* objects; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*,unsigned int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int debugstr_an (char const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  read_dword (char const**,int*) ; 

__attribute__((used)) static HRESULT d3dx9_copy_data(struct d3dx9_base_effect *base, unsigned int object_id, const char **ptr)
{
    struct d3dx_object *object = &base->objects[object_id];

    if (object->size || object->data)
    {
        if (object_id)
            FIXME("Overwriting object id %u!\n", object_id);
        else
            TRACE("Overwriting object id 0.\n");

        HeapFree(GetProcessHeap(), 0, object->data);
        object->data = NULL;
    }

    read_dword(ptr, &object->size);
    TRACE("Data size: %#x.\n", object->size);

    if (!object->size)
        return D3D_OK;

    object->data = HeapAlloc(GetProcessHeap(), 0, object->size);
    if (!object->data)
    {
        ERR("Failed to allocate object memory.\n");
        return E_OUTOFMEMORY;
    }

    TRACE("Data: %s.\n", debugstr_an(*ptr, object->size));
    memcpy(object->data, *ptr, object->size);

    *ptr += ((object->size + 3) & ~3);

    return D3D_OK;
}