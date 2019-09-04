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
struct array {int count; struct array* ptr; } ;
typedef  struct array WCHAR ;
typedef  int UINT ;
typedef  scalar_t__ CIMTYPE ;

/* Variables and functions */
 scalar_t__ CIM_DATETIME ; 
 scalar_t__ CIM_STRING ; 
 int get_type_size (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (struct array*) ; 

void destroy_array( struct array *array, CIMTYPE type )
{
    UINT i, size;

    if (!array) return;
    if (type == CIM_STRING || type == CIM_DATETIME)
    {
        size = get_type_size( type );
        for (i = 0; i < array->count; i++) heap_free( *(WCHAR **)((char *)array->ptr + i * size) );
    }
    heap_free( array->ptr );
    heap_free( array );
}