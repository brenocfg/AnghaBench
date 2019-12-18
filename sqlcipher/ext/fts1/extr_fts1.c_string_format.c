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
 int /*<<< orphan*/  assert (int) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static char *string_format(const char *zFormat,
                           const char *zDb, const char *zName){
  const char *p;
  size_t len = 0;
  size_t nDb = strlen(zDb);
  size_t nName = strlen(zName);
  size_t nFullTableName = nDb+1+nName;
  char *result;
  char *r;

  /* first compute length needed */
  for(p = zFormat ; *p ; ++p){
    len += (*p=='%' ? nFullTableName : 1);
  }
  len += 1;  /* for null terminator */

  r = result = malloc(len);
  for(p = zFormat; *p; ++p){
    if( *p=='%' ){
      memcpy(r, zDb, nDb);
      r += nDb;
      *r++ = '.';
      memcpy(r, zName, nName);
      r += nName;
    } else {
      *r++ = *p;
    }
  }
  *r++ = '\0';
  assert( r == result + len );
  return result;
}