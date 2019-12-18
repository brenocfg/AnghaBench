#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  const* attrs; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  attr_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_CONTEXTHANDLE ; 
 int /*<<< orphan*/  ATTR_IN ; 
 int /*<<< orphan*/  ATTR_OUT ; 
 int /*<<< orphan*/  ATTR_STRICTCONTEXTHANDLE ; 
 unsigned char NDR_CONTEXT_HANDLE_CANNOT_BE_NULL ; 
 unsigned char NDR_STRICT_CONTEXT_HANDLE ; 
 scalar_t__ is_attr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_ptr (TYPE_1__ const*) ; 

__attribute__((used)) static unsigned char get_contexthandle_flags( const type_t *iface, const attr_list_t *attrs,
                                              const type_t *type )
{
    unsigned char flags = 0;

    if (is_attr(iface->attrs, ATTR_STRICTCONTEXTHANDLE)) flags |= NDR_STRICT_CONTEXT_HANDLE;

    if (is_ptr(type) &&
        !is_attr( type->attrs, ATTR_CONTEXTHANDLE ) &&
        !is_attr( attrs, ATTR_CONTEXTHANDLE ))
        flags |= 0x80;

    if (is_attr(attrs, ATTR_IN))
    {
        flags |= 0x40;
        if (!is_attr(attrs, ATTR_OUT)) flags |= NDR_CONTEXT_HANDLE_CANNOT_BE_NULL;
    }
    if (is_attr(attrs, ATTR_OUT)) flags |= 0x20;

    return flags;
}