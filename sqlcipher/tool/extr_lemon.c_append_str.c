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
typedef  int /*<<< orphan*/  zInt ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int lemonStrlen (char const*) ; 
 int /*<<< orphan*/  lemon_sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  lemon_strcpy (char*,char*) ; 
 scalar_t__ realloc (char*,int) ; 

char *append_str(const char *zText, int n, int p1, int p2){
  static char empty[1] = { 0 };
  static char *z = 0;
  static int alloced = 0;
  static int used = 0;
  int c;
  char zInt[40];
  if( zText==0 ){
    if( used==0 && z!=0 ) z[0] = 0;
    used = 0;
    return z;
  }
  if( n<=0 ){
    if( n<0 ){
      used += n;
      assert( used>=0 );
    }
    n = lemonStrlen(zText);
  }
  if( (int) (n+sizeof(zInt)*2+used) >= alloced ){
    alloced = n + sizeof(zInt)*2 + used + 200;
    z = (char *) realloc(z,  alloced);
  }
  if( z==0 ) return empty;
  while( n-- > 0 ){
    c = *(zText++);
    if( c=='%' && n>0 && zText[0]=='d' ){
      lemon_sprintf(zInt, "%d", p1);
      p1 = p2;
      lemon_strcpy(&z[used], zInt);
      used += lemonStrlen(&z[used]);
      zText++;
      n--;
    }else{
      z[used++] = (char)c;
    }
  }
  z[used] = 0;
  return z;
}