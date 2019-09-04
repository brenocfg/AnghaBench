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
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT copy_substring_null(char *dest, int max_len, char *src)
{
    if (!src)
        return E_FAIL;

    if (max_len <= 0)
        return S_OK;

    if (!dest)
        return E_FAIL;

    while (*src && max_len-- > 1)
        *dest++ = *src++;
    *dest = 0;

    return S_OK;
}