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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ HDN_FIRST_UNICODE ; 
 scalar_t__ HDN_LAST ; 
 scalar_t__ HDN_UNICODE_OFFSET ; 

__attribute__((used)) static UINT HEADER_NotifyCodeWtoA(UINT code)
{
    /* we use the fact that all the unicode messages are in HDN_FIRST_UNICODE..HDN_LAST*/
    if (code >= HDN_LAST && code <= HDN_FIRST_UNICODE)
        return code + HDN_UNICODE_OFFSET;
    else
        return code;
}