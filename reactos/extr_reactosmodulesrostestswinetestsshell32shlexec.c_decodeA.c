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
typedef  int /*<<< orphan*/  decoded ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int decode_char (char const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 

__attribute__((used)) static char* decodeA(const char* str)
{
    static char decoded[1024];
    char*       ptr;
    size_t      len,i;

    len = strlen(str) / 2;
    if (!len--) return NULL;
    if (len >= sizeof(decoded))
    {
        fprintf(stderr, "string is too long!\n");
        assert(0);
    }
    ptr = decoded;
    for (i = 0; i < len; i++)
        ptr[i] = (decode_char(str[2 * i]) << 4) | decode_char(str[2 * i + 1]);
    ptr[len] = '\0';
    return ptr;
}