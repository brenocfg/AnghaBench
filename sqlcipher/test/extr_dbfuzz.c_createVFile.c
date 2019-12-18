#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sz; scalar_t__ zFilename; scalar_t__ a; scalar_t__ nRef; } ;
typedef  TYPE_1__ VFile ;
struct TYPE_6__ {TYPE_1__* aFile; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MX_FILE ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  fatalError (char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 TYPE_1__* findVFile (char const*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (scalar_t__,long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 TYPE_2__ g ; 
 void* malloc (long) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static VFile *createVFile(const char *zName, const char *zDiskFile){
  VFile *pNew = findVFile(zName);
  int i;
  FILE *in = 0;
  long sz = 0;

  if( pNew ) return pNew;
  for(i=0; i<MX_FILE && g.aFile[i].sz>=0; i++){}
  if( i>=MX_FILE ) return 0;
  if( zDiskFile ){
    in = fopen(zDiskFile, "rb");
    if( in==0 ) fatalError("no such file: \"%s\"", zDiskFile);
    fseek(in, 0, SEEK_END);
    sz = ftell(in);
    rewind(in);
  }
  pNew = &g.aFile[i];
  if( zName ){
    int nName = (int)strlen(zName)+1;
    pNew->zFilename = malloc(nName);
    if( pNew->zFilename==0 ){
      if( in ) fclose(in);
      return 0;
    }
    memcpy(pNew->zFilename, zName, nName);
  }else{
    pNew->zFilename = 0;
  }
  pNew->nRef = 0;
  pNew->sz = sz;
  pNew->a = malloc(sz);
  if( sz>0 ){
    if( pNew->a==0 || fread(pNew->a, sz, 1, in)<1 ){
      free(pNew->zFilename);
      free(pNew->a);
      pNew->a = 0;
      pNew->zFilename = 0;
      pNew->sz = -1;
      pNew = 0;
    }
  }
  if( in ) fclose(in);
  return pNew;
}