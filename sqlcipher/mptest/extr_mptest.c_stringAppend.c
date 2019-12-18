#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int n; int nAlloc; char* z; } ;
typedef  TYPE_1__ String ;

/* Variables and functions */
 int /*<<< orphan*/  fatalError (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* sqlite3_realloc (char*,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void stringAppend(String *p, const char *z, int n){
  if( n<0 ) n = (int)strlen(z);
  if( p->n+n>=p->nAlloc ){
    int nAlloc = p->nAlloc*2 + n + 100;
    char *zNew = sqlite3_realloc(p->z, nAlloc);
    if( zNew==0 ) fatalError("out of memory");
    p->z = zNew;
    p->nAlloc = nAlloc;
  }
  memcpy(p->z+p->n, z, n);
  p->n += n;
  p->z[p->n] = 0;
}