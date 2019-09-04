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
struct TYPE_3__ {int len; char* ptr; } ;
typedef  TYPE_1__ xmlstr_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  strncmpW (char*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static inline BOOL xmlstr_cmp_end(const xmlstr_t* xmlstr, const WCHAR *str)
{
    return (xmlstr->len && xmlstr->ptr[0] == '/' &&
            !strncmpW(xmlstr->ptr + 1, str, xmlstr->len - 1) && !str[xmlstr->len - 1]);
}