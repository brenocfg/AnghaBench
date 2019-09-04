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
struct fontlist {char* name; int len; scalar_t__ isascii; scalar_t__ isbinary; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 unsigned int getErrorCnt (struct fontlist*) ; 
 int getRandom (int,int) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int
  copyfont( struct fontlist*  item,
            char*             newfont )
  {
    static char   buffer[8096];
    FILE          *good, *newf;
    size_t        len;
    unsigned int  i, err_cnt;


    good = fopen( item->name, "r" );
    if ( !good )
    {
      fprintf( stderr, "Can't open `%s'\n", item->name );
      return false;
    }

    newf = fopen( newfont, "w+" );
    if ( !newf )
    {
      fprintf( stderr, "Can't create temporary output file `%s'\n",
               newfont );
      exit( 1 );
    }

    while ( ( len = fread( buffer, 1, sizeof ( buffer ), good ) ) > 0 )
      fwrite( buffer, 1, len, newf );

    fclose( good );

    err_cnt = getErrorCnt( item );
    for ( i = 0; i < err_cnt; i++ )
    {
      fseek( newf, getRandom( 0, (int)( item->len - 1 ) ), SEEK_SET );

      if ( item->isbinary )
        putc( getRandom( 0, 0xFF ), newf );
      else if ( item->isascii )
        putc( getRandom( 0x20, 0x7E ), newf );
      else
      {
        int  hex = getRandom( 0, 15 );


        if ( hex < 10 )
          hex += '0';
        else
          hex += 'A' - 10;

        putc( hex, newf );
      }
    }

    if ( ferror( newf ) )
    {
      fclose( newf );
      unlink( newfont );
      return false;
    }

    fclose( newf );

    return true;
  }