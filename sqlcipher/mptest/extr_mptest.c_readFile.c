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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  fatalError (char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fread (char*,int,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 char* sqlite3_malloc (long) ; 

__attribute__((used)) static char *readFile(const char *zFilename){
  FILE *in = fopen(zFilename, "rb");
  long sz;
  char *z;
  if( in==0 ){
    fatalError("cannot open \"%s\" for reading", zFilename);
  }
  fseek(in, 0, SEEK_END);
  sz = ftell(in);
  rewind(in);
  z = sqlite3_malloc( sz+1 );
  sz = (long)fread(z, 1, sz, in);
  z[sz] = 0;
  fclose(in);
  return z;
}