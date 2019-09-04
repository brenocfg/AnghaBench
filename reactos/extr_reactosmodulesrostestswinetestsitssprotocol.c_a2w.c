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
typedef  int /*<<< orphan*/  const WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static const WCHAR *a2w(const char *str)
{
    static WCHAR bufs[8][128];
    static int i;

    if(!str)
        return NULL;

    i = (i+1) % 8;
    MultiByteToWideChar(CP_ACP, 0, str, -1, bufs[i], 128);
    return bufs[i];
}