#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_size; } ;
typedef  int ssize_t ;
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_9__ {char* psz_file_template; scalar_t__ psz_token; } ;
typedef  TYPE_2__ filter_sys_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SVG_TEMPLATE_BODY_TOKEN ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int fread (char*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,unsigned long,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,char*) ; 
 scalar_t__ strstr (char*,int /*<<< orphan*/ ) ; 
 char* var_InheritString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * vlc_fopen (char*,char*) ; 

__attribute__((used)) static void svg_LoadTemplate( filter_t *p_filter )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    char *psz_template = NULL;
    char *psz_filename = var_InheritString( p_filter, "svg-template-file" );
    if( psz_filename && psz_filename[0] )
    {
        /* Read the template */
        FILE *file = vlc_fopen( psz_filename, "rt" );
        if( !file )
        {
            msg_Warn( p_filter, "SVG template file %s does not exist.",
                                         psz_filename );
        }
        else
        {
            struct stat s;
            if( fstat( fileno( file ), &s ) || ((signed)s.st_size) < 0 )
            {
                msg_Err( p_filter, "SVG template invalid" );
            }
            else
            {
                msg_Dbg( p_filter, "reading %ld bytes from template %s",
                         (unsigned long)s.st_size, psz_filename );

                psz_template = malloc( s.st_size + 1 );
                if( psz_template )
                {
                    psz_template[ s.st_size ] = 0;
                    ssize_t i_read = fread( psz_template, s.st_size, 1, file );
                    if( i_read != 1 )
                    {
                        free( psz_template );
                        psz_template = NULL;
                    }
                }
            }
            fclose( file );
        }
    }
    free( psz_filename );

    if( psz_template )
    {
        p_sys->psz_token = strstr( psz_template, SVG_TEMPLATE_BODY_TOKEN );
        if( !p_sys->psz_token )
        {
            msg_Err( p_filter, "'%s' not found in SVG template", SVG_TEMPLATE_BODY_TOKEN );
            free( psz_template );
        }
        else *((char*)p_sys->psz_token) = 0;
    }

    p_sys->psz_file_template = psz_template;
}