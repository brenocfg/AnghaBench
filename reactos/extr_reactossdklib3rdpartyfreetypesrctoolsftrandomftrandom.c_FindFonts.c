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
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
struct fontlist {int dummy; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_5__ {int /*<<< orphan*/ * name; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ extmatch (char*,char**) ; 
 unsigned int fcnt ; 
 int /*<<< orphan*/  figurefiletype (TYPE_1__*) ; 
 TYPE_1__* fontlist ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 TYPE_1__* realloc (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strdup (char*) ; 

__attribute__((used)) static void
  FindFonts( char**  fontdirs,
             char**  extensions )
  {
    int           i;
    unsigned int  max;
    char          buffer[1025];
    struct stat   statb;


    max  = 0;
    fcnt = 0;

    for ( i = 0; fontdirs[i] != NULL; i++ )
    {
      DIR*            examples;
      struct dirent*  ent;


      examples = opendir( fontdirs[i] );
      if ( !examples )
      {
        fprintf( stderr,
                 "Can't open example font directory `%s'\n",
                 fontdirs[i] );
        exit( 1 );
      }

      while ( ( ent = readdir( examples ) ) != NULL )
      {
        snprintf( buffer, sizeof ( buffer ),
                  "%s/%s", fontdirs[i], ent->d_name );
        if ( stat( buffer, &statb ) == -1 || S_ISDIR( statb.st_mode ) )
          continue;
        if ( !extensions || extmatch( buffer, extensions ) )
        {
          if ( fcnt >= max )
          {
            max += 100;
            fontlist = realloc( fontlist, max * sizeof ( struct fontlist ) );
            if ( !fontlist )
            {
              fprintf( stderr, "Can't allocate memory\n" );
              exit( 1 );
            }
          }

          fontlist[fcnt].name = strdup( buffer );
          fontlist[fcnt].len  = statb.st_size;

          figurefiletype( &fontlist[fcnt] );
          fcnt++;
        }
      }

      closedir( examples );
    }

    if ( fcnt == 0 )
    {
      fprintf( stderr, "Can't find matching font files.\n" );
      exit( 1 );
    }

    fontlist[fcnt].name = NULL;
  }