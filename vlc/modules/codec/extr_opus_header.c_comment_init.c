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
 int /*<<< orphan*/  SetDWLE (char*,size_t) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static char *comment_init(size_t *length, const char *vendor)
{
    /*The 'vendor' field should be the actual encoding library used.*/
    if (!vendor)
        vendor = "unknown";
    size_t vendor_length = strlen(vendor);

    size_t user_comment_list_length = 0;
    size_t len = 8 + 4 + vendor_length + 4;
    char *p = malloc(len);
    if (p == NULL)
        return NULL;

    memcpy(p, "OpusTags", 8);
    SetDWLE(p + 8, vendor_length);
    memcpy(p + 12, vendor, vendor_length);
    SetDWLE(p + 12 + vendor_length, user_comment_list_length);

    *length = len;
    return p;
}