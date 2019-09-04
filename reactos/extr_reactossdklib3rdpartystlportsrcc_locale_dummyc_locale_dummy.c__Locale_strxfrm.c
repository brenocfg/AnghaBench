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

/* Variables and functions */
 int /*<<< orphan*/  _STLP_STRNCPY (char*,size_t,char const*,size_t) ; 

size_t _Locale_strxfrm(struct _Locale_collate* lcol,
                       char* dest, size_t dest_n,
                       const char* src, size_t src_n) {
  if (dest != 0) {
    _STLP_STRNCPY(dest, dest_n, src, dest_n - 1); dest[dest_n - 1] = 0;
  }
  return src_n;
}