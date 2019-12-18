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
struct TYPE_3__ {scalar_t__ ptr; scalar_t__ len; } ;
typedef  TYPE_1__ xmlstr_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int BOOL ;

/* Variables and functions */
 int TRUE ; 
 scalar_t__ strlenW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strncmpW (scalar_t__,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static inline BOOL xml_elem_cmp(const xmlstr_t *elem, const WCHAR *str, const WCHAR *namespace)
{
    UINT len = strlenW( namespace );

    if (!strncmpW(elem->ptr, str, elem->len) && !str[elem->len]) return TRUE;
    return (elem->len > len && !strncmpW(elem->ptr, namespace, len) &&
            !strncmpW(elem->ptr + len, str, elem->len - len) && !str[elem->len - len]);
}