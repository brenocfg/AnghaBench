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
 int /*<<< orphan*/  MemoryCheck (char const*) ; 
 char* Strsafe_find (char const*) ; 
 int /*<<< orphan*/  Strsafe_insert (char const*) ; 
 scalar_t__ lemonStrlen (char const*) ; 
 int /*<<< orphan*/  lemon_strcpy (char*,char const*) ; 
 scalar_t__ malloc (scalar_t__) ; 

const char *Strsafe(const char *y)
{
  const char *z;
  char *cpy;

  if( y==0 ) return 0;
  z = Strsafe_find(y);
  if( z==0 && (cpy=(char *)malloc( lemonStrlen(y)+1 ))!=0 ){
    lemon_strcpy(cpy,y);
    z = cpy;
    Strsafe_insert(z);
  }
  MemoryCheck(z);
  return z;
}