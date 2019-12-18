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
struct _Locale_collate {int dummy; } ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 size_t strxfrm_l (char*,char const*,size_t,int /*<<< orphan*/ ) ; 

size_t _Locale_strxfrm(struct _Locale_collate *__loc,
                       char *dest, size_t dest_n,
                       const char *src, size_t src_n )
{
  const char *real_src;
  char *buf = NULL;
  size_t result;

  if (src_n == 0)
  {
    if (dest != NULL) dest[0] = 0;
    return 0;
  }
  if (src[src_n] != 0) {
    buf = malloc(src_n + 1);
    strncpy(buf, src, src_n);
    buf[src_n] = 0;
    real_src = buf;
  }
  else
    real_src = src;
  result = strxfrm_l(dest, real_src, dest_n, (locale_t)__loc);
  if (buf != NULL) free(buf);
  return result;
}