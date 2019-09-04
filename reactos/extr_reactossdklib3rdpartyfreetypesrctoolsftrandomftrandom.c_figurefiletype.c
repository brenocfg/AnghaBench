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
struct fontlist {int isbinary; int isascii; int ishex; char* name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static void
  figurefiletype( struct fontlist*  item )
  {
    FILE*  foo;


    item->isbinary = item->isascii = item->ishex = false;

    foo = fopen( item->name, "rb" );
    if ( foo )
    {
      /* Try to guess the file type from the first few characters... */
      int  ch1 = getc( foo );
      int  ch2 = getc( foo );
      int  ch3 = getc( foo );
      int  ch4 = getc( foo );


      fclose( foo );

      if ( ( ch1 == 0   && ch2 == 1   && ch3 == 0   && ch4 == 0   ) ||
           ( ch1 == 'O' && ch2 == 'T' && ch3 == 'T' && ch4 == 'O' ) ||
           ( ch1 == 't' && ch2 == 'r' && ch3 == 'u' && ch4 == 'e' ) ||
           ( ch1 == 't' && ch2 == 't' && ch3 == 'c' && ch4 == 'f' ) )
      {
        /* ttf, otf, ttc files */
        item->isbinary = true;
      }
      else if ( ch1 == 0x80 && ch2 == '\01' )
      {
        /* PFB header */
        item->isbinary = true;
      }
      else if ( ch1 == '%' && ch2 == '!' )
      {
        /* Random PostScript */
        if ( strstr( item->name, ".pfa" ) ||
             strstr( item->name, ".PFA" ) )
          item->ishex = true;
        else
          item->isascii = true;
      }
      else if ( ch1 == 1 && ch2 == 0 && ch3 == 4 )
      {
        /* Bare CFF */
        item->isbinary = true;
      }
      else if ( ch1 == 'S' && ch2 == 'T' && ch3 == 'A' && ch4 == 'R' )
      {
        /* BDF */
        item->ishex = true;
      }
      else if ( ch1 == 'P' && ch2 == 'F' && ch3 == 'R' && ch4 == '0' )
      {
        /* PFR */
        item->isbinary = true;
      }
      else if ( ( ch1 == '\1' && ch2 == 'f' && ch3 == 'c' && ch4 == 'p' ) ||
                ( ch1 == 'M'  && ch2 == 'Z' )                             )
      {
        /* Windows FON */
        item->isbinary = true;
      }
      else
      {
        fprintf( stderr,
                 "Can't recognize file type of `%s', assuming binary\n",
                 item->name );
        item->isbinary = true;
      }
    }
    else
    {
      fprintf( stderr, "Can't open `%s' for typing the file.\n",
               item->name );
      item->isbinary = true;
    }
  }