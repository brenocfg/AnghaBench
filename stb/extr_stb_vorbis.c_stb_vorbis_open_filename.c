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
typedef  int /*<<< orphan*/  stb_vorbis_alloc ;
typedef  int /*<<< orphan*/  stb_vorbis ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int VORBIS_file_open_failure ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fopen_s (int /*<<< orphan*/ **,char const*,char*) ; 
 int /*<<< orphan*/ * stb_vorbis_open_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/  const*) ; 

stb_vorbis * stb_vorbis_open_filename(const char *filename, int *error, const stb_vorbis_alloc *alloc)
{
   FILE *f;
#if defined(_WIN32) && defined(__STDC_WANT_SECURE_LIB__)
   if (0 != fopen_s(&f, filename, "rb"))
      f = NULL;
#else
   f = fopen(filename, "rb");
#endif
   if (f) 
      return stb_vorbis_open_file(f, TRUE, error, alloc);
   if (error) *error = VORBIS_file_open_failure;
   return NULL;
}