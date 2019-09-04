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
struct TYPE_3__ {size_t member_1; int /*<<< orphan*/  const* member_0; } ;
typedef  TYPE_1__ substr_t ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */

__attribute__((used)) static inline substr_t substr(const WCHAR *str, size_t len)
{
    substr_t r = {str, len};
    return r;
}