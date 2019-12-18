#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* str; } ;
typedef  TYPE_1__ GString ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  g_string_append (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  g_string_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_string_new (char*) ; 

char* strjoin_n (const char *seperator, int argc, char **argv)
{
    GString *buf;
    int i;
    char *str;

    if (argc == 0)
        return NULL;
    
    buf = g_string_new (argv[0]);
    for (i = 1; i < argc; ++i) {
        g_string_append (buf, seperator);
        g_string_append (buf, argv[i]);
    }

    str = buf->str;
    g_string_free (buf, FALSE);
    return str;
}