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
 int /*<<< orphan*/  G_NORMALIZE_NFC ; 
 char* g_utf8_normalize (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_utf8_validate (char const*,int,int /*<<< orphan*/ *) ; 

char *
normalize_utf8_path (const char *path)
{
    if (!g_utf8_validate (path, -1, NULL))
        return NULL;
    return g_utf8_normalize (path, -1, G_NORMALIZE_NFC);
}