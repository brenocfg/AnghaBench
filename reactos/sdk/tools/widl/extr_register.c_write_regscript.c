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
typedef  int /*<<< orphan*/  type_t ;
typedef  int /*<<< orphan*/  statement_list_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  add_output_to_resources (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ do_everything ; 
 int /*<<< orphan*/  do_regscript ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_ps_factory (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  flush_output_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fwrite (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  indent ; 
 int /*<<< orphan*/  init_output_buffer () ; 
 int /*<<< orphan*/  need_proxy_file (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  output_buffer ; 
 scalar_t__ output_buffer_pos ; 
 int /*<<< orphan*/  put_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regscript_name ; 
 int /*<<< orphan*/  regscript_token ; 
 scalar_t__ strendswith (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_coclasses (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_interfaces (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  write_progids (int /*<<< orphan*/  const*) ; 

void write_regscript( const statement_list_t *stmts )
{
    const type_t *ps_factory;

    if (!do_regscript) return;
    if (do_everything && !need_proxy_file( stmts )) return;

    init_output_buffer();

    put_str( indent, "HKCR\n" );
    put_str( indent++, "{\n" );

    put_str( indent, "NoRemove Interface\n" );
    put_str( indent++, "{\n" );
    ps_factory = find_ps_factory( stmts );
    if (ps_factory) write_interfaces( stmts, ps_factory );
    put_str( --indent, "}\n" );

    put_str( indent, "NoRemove CLSID\n" );
    put_str( indent++, "{\n" );
    write_coclasses( stmts, NULL );
    put_str( --indent, "}\n" );

    write_progids( stmts );
    put_str( --indent, "}\n" );

    if (strendswith( regscript_name, ".res" ))  /* create a binary resource file */
    {
        add_output_to_resources( "WINE_REGISTRY", regscript_token );
        flush_output_resources( regscript_name );
    }
    else
    {
        FILE *f = fopen( regscript_name, "w" );
        if (!f) error( "Could not open %s for output\n", regscript_name );
        if (fwrite( output_buffer, 1, output_buffer_pos, f ) != output_buffer_pos)
            error( "Failed to write to %s\n", regscript_name );
        if (fclose( f ))
            error( "Failed to write to %s\n", regscript_name );
    }
}