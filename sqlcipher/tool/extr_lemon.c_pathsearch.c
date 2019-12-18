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
 scalar_t__ access (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 size_t lemonStrlen (char const*) ; 
 int /*<<< orphan*/  lemon_sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  lemon_strcpy (char*,char const*) ; 
 scalar_t__ malloc (size_t) ; 
 char* strchr (char*,char) ; 
 char* strrchr (char*,char) ; 

char *pathsearch(char *argv0, char *name, int modemask)
{
  const char *pathlist;
  char *pathbufptr;
  char *pathbuf;
  char *path,*cp;
  char c;

#ifdef __WIN32__
  cp = strrchr(argv0,'\\');
#else
  cp = strrchr(argv0,'/');
#endif
  if( cp ){
    c = *cp;
    *cp = 0;
    path = (char *)malloc( lemonStrlen(argv0) + lemonStrlen(name) + 2 );
    if( path ) lemon_sprintf(path,"%s/%s",argv0,name);
    *cp = c;
  }else{
    pathlist = getenv("PATH");
    if( pathlist==0 ) pathlist = ".:/bin:/usr/bin";
    pathbuf = (char *) malloc( lemonStrlen(pathlist) + 1 );
    path = (char *)malloc( lemonStrlen(pathlist)+lemonStrlen(name)+2 );
    if( (pathbuf != 0) && (path!=0) ){
      pathbufptr = pathbuf;
      lemon_strcpy(pathbuf, pathlist);
      while( *pathbuf ){
        cp = strchr(pathbuf,':');
        if( cp==0 ) cp = &pathbuf[lemonStrlen(pathbuf)];
        c = *cp;
        *cp = 0;
        lemon_sprintf(path,"%s/%s",pathbuf,name);
        *cp = c;
        if( c==0 ) pathbuf[0] = 0;
        else pathbuf = &cp[1];
        if( access(path,modemask)==0 ) break;
      }
      free(pathbufptr);
    }
  }
  return path;
}