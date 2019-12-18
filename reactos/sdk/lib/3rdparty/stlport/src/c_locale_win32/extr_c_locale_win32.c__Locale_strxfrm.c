#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ lc; int /*<<< orphan*/  cp; } ;
typedef  TYPE_2__ _Locale_collate_t ;

/* Variables and functions */
 size_t INT_MAX ; 
 int /*<<< orphan*/  LCMAP_SORTKEY ; 
 int LCMapStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char*,int) ; 
 int /*<<< orphan*/  _STLP_STRNCPY (char*,size_t,char const*,size_t) ; 
 char* __ConvertToCP (scalar_t__,scalar_t__,char const*,size_t,size_t*) ; 
 scalar_t__ __GetDefaultCP (int /*<<< orphan*/ ) ; 
 scalar_t__ atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 

size_t _Locale_strxfrm(_Locale_collate_t* lcol,
                       char* dst, size_t dst_size,
                       const char* src, size_t src_size) {
  int result;

  /* The Windows API do not support transformation of very long strings (src_size > INT_MAX)
   * In this case the result will just be the input string:
   */
  if (src_size > INT_MAX) {
    if (dst != 0) {
      _STLP_STRNCPY(dst, dst_size, src, src_size);
    }
    return src_size;
  }
  if (dst_size > INT_MAX) {
    /* now that we know that src_size <= INT_MAX we can safely decrease dst_size to INT_MAX. */
    dst_size = INT_MAX;
  }

  if (__GetDefaultCP(lcol->lc.id) == atoi(lcol->cp))
    result = LCMapStringA(lcol->lc.id, LCMAP_SORTKEY, src, (int)src_size, dst, (int)dst_size);
  else {
    char *buf;
    size_t size;
    buf = __ConvertToCP(atoi(lcol->cp), __GetDefaultCP(lcol->lc.id), src, src_size, &size);

    result = LCMapStringA(lcol->lc.id, LCMAP_SORTKEY, buf, (int)size, dst, (int)dst_size);
    free(buf);
  }
  return result != 0 ? result - 1 : 0;
}