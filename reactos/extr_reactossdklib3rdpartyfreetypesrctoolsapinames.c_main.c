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
typedef  int /*<<< orphan*/  OutputFormat ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  OUTPUT_BORLAND_DEF ; 
 int /*<<< orphan*/  OUTPUT_LIST ; 
 int /*<<< orphan*/  OUTPUT_NETWARE_IMP ; 
 int /*<<< orphan*/  OUTPUT_WATCOM_LBC ; 
 int /*<<< orphan*/  OUTPUT_WINDOWS_DEF ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const* const,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const* const) ; 
 int /*<<< orphan*/  names_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  names_sort () ; 
 scalar_t__ num_names ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  read_header_file (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  usage () ; 

int  main( int argc, const char* const*  argv )
{
  int           from_stdin = 0;
  int           verbose = 0;
  OutputFormat  format = OUTPUT_LIST;  /* the default */
  FILE*         out    = stdout;
  const char*   library_name = NULL;

  if ( argc < 2 )
    usage();

  /* '-' used as a single argument means read source file from stdin */
  while ( argc > 1 && argv[1][0] == '-' )
  {
    const char*  arg = argv[1];

    switch ( arg[1] )
    {
      case 'v':
        verbose = 1;
        break;

      case 'o':
        if ( arg[2] == 0 )
        {
          if ( argc < 2 )
            usage();

          arg = argv[2];
          argv++;
          argc--;
        }
        else
          arg += 2;

        out = fopen( arg, "wt" );
        if ( !out )
        {
          fprintf( stderr, "could not open '%s' for writing\n", argv[2] );
          exit(3);
        }
        break;

      case 'd':
        if ( arg[2] == 0 )
        {
          if ( argc < 2 )
            usage();

          arg = argv[2];
          argv++;
          argc--;
        }
        else
          arg += 2;

        library_name = arg;
        break;

      case 'w':
        format = OUTPUT_WINDOWS_DEF;
        switch ( arg[2] )
        {
          case 'B':
            format = OUTPUT_BORLAND_DEF;
            break;

          case 'W':
            format = OUTPUT_WATCOM_LBC;
            break;

          case 'N':
            format = OUTPUT_NETWARE_IMP;
            break;

          case 0:
            break;

          default:
            usage();
        }
        break;

      case 0:
        from_stdin = 1;
        break;

      default:
        usage();
    }

    argc--;
    argv++;
  }

  if ( from_stdin )
  {
    read_header_file( stdin, verbose );
  }
  else
  {
    for ( --argc, argv++; argc > 0; argc--, argv++ )
    {
      FILE*  file = fopen( argv[0], "rb" );

      if ( !file )
        fprintf( stderr, "unable to open '%s'\n", argv[0] );
      else
      {
        if ( verbose )
          fprintf( stderr, "opening '%s'\n", argv[0] );

        read_header_file( file, verbose );
        fclose( file );
      }
    }
  }

  if ( num_names == 0 )
    panic( "could not find exported functions !!\n" );

  names_sort();
  names_dump( out, format, library_name );

  if ( out != stdout )
    fclose( out );

  return 0;
}