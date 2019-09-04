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
typedef  int WCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int* uri_char_table ; 

__attribute__((used)) static inline BOOL is_uri_unescaped(WCHAR c)
{
    return c < 128 && uri_char_table[c] == 2;
}