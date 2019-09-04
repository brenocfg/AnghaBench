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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline DWORD subtract_bytes(DWORD len, DWORD bytes)
{
    if(bytes > len){
        TRACE("Apparent mismatch in chunk lengths? %u bytes remaining, %u bytes read\n", len, bytes);
        return 0;
    }
    return len - bytes;
}