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
struct TYPE_3__ {char* zout; char* zout_start; int /*<<< orphan*/ * zbuffer_end; int /*<<< orphan*/ * zbuffer; } ;
typedef  TYPE_1__ zbuf ;
typedef  int /*<<< orphan*/  stbi__uint8 ;

/* Variables and functions */
 scalar_t__ do_zlib (TYPE_1__*,char*,int,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 

char *stbi_zlib_decode_malloc_guesssize_headerflag(const char *buffer, int len, int initial_size, int *outlen, int parse_header)
{
   zbuf a;
   char *p = (char *) malloc(initial_size);
   if (p == NULL) return NULL;
   a.zbuffer = (stbi__uint8 *) buffer;
   a.zbuffer_end = (stbi__uint8 *) buffer + len;
   if (do_zlib(&a, p, initial_size, 1, parse_header)) {
      if (outlen) *outlen = (int) (a.zout - a.zout_start);
      return a.zout_start;
   } else {
      free(a.zout_start);
      return NULL;
   }
}