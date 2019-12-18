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

/* Variables and functions */
 size_t ngx_base64_encoded_length (size_t) ; 

__attribute__((used)) static size_t
ngx_http_lua_base64_encoded_length(size_t n, int no_padding)
{
    return no_padding ? (n * 8 + 5) / 6 : ngx_base64_encoded_length(n);
}