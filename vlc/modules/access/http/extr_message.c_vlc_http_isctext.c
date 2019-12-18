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

__attribute__((used)) static int vlc_http_isctext(int c)
{   /* IETF RFC7230 §3.2.6 */
    return (c == '\t') || (c == ' ') || (c >= 0x21 && c <= 0x27)
        || (c >= 0x2A && c <= 0x5B) || (c >= 0x5D && c <= 0x7E)
        || (c >= 0x80);
}