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
 int /*<<< orphan*/  G_NORMALIZE_ALL_COMPOSE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int g_utf8_collate (char*,char*) ; 
 char* g_utf8_normalize (char const*,int,int /*<<< orphan*/ ) ; 
 char* g_utf8_offset_to_pointer (char*,size_t) ; 

int utf8_strncmp ( const char* a, const char* b, size_t n )
{
    char *na = g_utf8_normalize ( a, -1, G_NORMALIZE_ALL_COMPOSE );
    char *nb = g_utf8_normalize ( b, -1, G_NORMALIZE_ALL_COMPOSE );
    *g_utf8_offset_to_pointer ( na, n ) = '\0';
    *g_utf8_offset_to_pointer ( nb, n ) = '\0';
    int r = g_utf8_collate ( na, nb );
    g_free ( na );
    g_free ( nb );
    return r;
}