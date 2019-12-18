#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  char gchar ;
struct TYPE_3__ {scalar_t__* columns; int /*<<< orphan*/  column_separator; } ;
typedef  TYPE_1__ DmenuModePrivateData ;

/* Variables and functions */
 int /*<<< orphan*/  G_REGEX_CASELESS ; 
 scalar_t__ g_ascii_strtoull (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char** g_regex_split_simple (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int) ; 
 char* g_strdup (char const*) ; 
 int /*<<< orphan*/  g_strfreev (char**) ; 
 char* g_strjoin (char*,char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static gchar * dmenu_format_output_string ( const DmenuModePrivateData *pd, const char *input )
{
    if ( pd->columns == NULL ) {
        return g_strdup ( input );
    }
    char     *retv       = NULL;
    char     ** splitted = g_regex_split_simple ( pd->column_separator, input, G_REGEX_CASELESS, 00 );
    uint32_t ns          = 0;
    for (; splitted && splitted[ns]; ns++ ) {
        ;
    }
    for ( uint32_t i = 0; pd->columns && pd->columns[i]; i++ ) {
        unsigned int index = (unsigned int ) g_ascii_strtoull ( pd->columns[i], NULL, 10 );
        if ( index < ns && index > 0 ) {
            if ( retv == NULL ) {
                retv = g_strdup ( splitted[index - 1] );
            }
            else {
                gchar *t = g_strjoin ( "\t", retv, splitted[index - 1], NULL );
                g_free ( retv );
                retv = t;
            }
        }
    }
    g_strfreev ( splitted );
    return retv ? retv : g_strdup ( "" );
}