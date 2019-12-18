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
struct dstr {int nUsed; int nAlloc; char* z; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,char const*,int) ; 
 int /*<<< orphan*/  memset (struct dstr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_realloc (char*,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void dstrAppend(struct dstr *p, const char *z, int divider){
  int n = (int)strlen(z);
  if( p->nUsed + n + 2 > p->nAlloc ){
    char *zNew;
    p->nAlloc = p->nAlloc*2 + n + 200;
    zNew = sqlite3_realloc(p->z, p->nAlloc);
    if( zNew==0 ){
      sqlite3_free(p->z);
      memset(p, 0, sizeof(*p));
      return;
    }
    p->z = zNew;
  }
  if( divider && p->nUsed>0 ){
    p->z[p->nUsed++] = divider;
  }
  memcpy(&p->z[p->nUsed], z, n+1);
  p->nUsed += n;
}