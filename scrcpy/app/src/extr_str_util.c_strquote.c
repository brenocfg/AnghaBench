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
 char* SDL_malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

char *
strquote(const char *src) {
    size_t len = strlen(src);
    char *quoted = SDL_malloc(len + 3);
    if (!quoted) {
        return NULL;
    }
    memcpy(&quoted[1], src, len);
    quoted[0] = '"';
    quoted[len + 1] = '"';
    quoted[len + 2] = '\0';
    return quoted;
}