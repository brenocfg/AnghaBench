#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_uint64 ;
struct TYPE_4__ {int n; int nAlloc; int oomErr; char* z; } ;
typedef  TYPE_1__ Str ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_realloc64 (char*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void StrAppend(Str *p, const char *z){
  sqlite3_uint64 n = strlen(z);
  if( p->n + n >= p->nAlloc ){
    char *zNew;
    sqlite3_uint64 nNew;
    if( p->oomErr ) return;
    nNew = p->nAlloc*2 + 100 + n;
    zNew = sqlite3_realloc64(p->z, nNew);
    if( zNew==0 ){
      sqlite3_free(p->z);
      memset(p, 0, sizeof(*p));
      p->oomErr = 1;
      return;
    }
    p->z = zNew;
    p->nAlloc = nNew;
  }
  memcpy(p->z + p->n, z, (int)n);
  p->n += n;
  p->z[p->n] = 0;
}