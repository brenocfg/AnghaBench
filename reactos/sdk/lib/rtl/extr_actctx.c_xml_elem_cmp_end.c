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
struct TYPE_4__ {char* ptr; scalar_t__ len; } ;
typedef  TYPE_1__ xmlstr_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  xml_elem_cmp (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline BOOL xml_elem_cmp_end(const xmlstr_t *elem, const WCHAR *str, const WCHAR *namespace)
{
    if (elem->len && elem->ptr[0] == '/')
    {
        xmlstr_t elem_end;
        elem_end.ptr = elem->ptr + 1;
        elem_end.len = elem->len - 1;
        return xml_elem_cmp( &elem_end, str, namespace );
    }
    return FALSE;
}