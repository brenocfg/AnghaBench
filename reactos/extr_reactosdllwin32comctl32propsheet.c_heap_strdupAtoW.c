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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/ * Alloc (int) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static WCHAR *heap_strdupAtoW(const char *str)
{
    WCHAR *ret;
    INT len;

    len = MultiByteToWideChar(CP_ACP, 0, str, -1, 0, 0);
    ret = Alloc(len * sizeof(WCHAR));
    MultiByteToWideChar(CP_ACP, 0, str, -1, ret, len);

    return ret;
}