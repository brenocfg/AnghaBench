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
typedef  int /*<<< orphan*/  GFile ;

/* Variables and functions */
 char* g_build_filename (char*,char*,int /*<<< orphan*/ *) ; 
 char* g_file_get_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_file_new_for_path (char*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 char* g_path_get_dirname (char const*) ; 
 int /*<<< orphan*/  g_path_is_absolute (char*) ; 
 char* rofi_expand_path (char const*) ; 

char * rofi_theme_parse_prepare_file ( const char *file, const char *parent_file )
{
    char *filename = rofi_expand_path ( file );
    // If no absolute path specified, expand it.
    if ( parent_file != NULL && !g_path_is_absolute ( filename )   ) {
        char *basedir = g_path_get_dirname ( parent_file );
        char *path    = g_build_filename ( basedir, filename, NULL );
        g_free ( filename );
        filename = path;
        g_free ( basedir );
    }
    GFile *gf = g_file_new_for_path ( filename );
    g_free ( filename );
    filename = g_file_get_path ( gf );
    g_object_unref ( gf );

    return filename;
}