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
typedef  int /*<<< orphan*/  stbi_uc ;
typedef  int /*<<< orphan*/  stbi ;

/* Variables and functions */
 scalar_t__ at_eof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * convert_format (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/ * epuc (char*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int get16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get8 (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pic_load2 (int /*<<< orphan*/ *,int,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static stbi_uc *pic_load(stbi *s,int *px,int *py,int *comp,int req_comp)
{
   stbi_uc *result;
   int i, x,y;

   for (i=0; i<92; ++i)
      get8(s);

   x = get16(s);
   y = get16(s);
   if (at_eof(s))  return epuc("bad file","file too short (pic header)");
   if ((1 << 28) / x < y) return epuc("too large", "Image too large to decode");

   get32(s); //skip `ratio'
   get16(s); //skip `fields'
   get16(s); //skip `pad'

   // intermediate buffer is RGBA
   result = (stbi_uc *) malloc(x*y*4);
   memset(result, 0xff, x*y*4);

   if (!pic_load2(s,x,y,comp, result)) {
      free(result);
      result=0;
   }
   *px = x;
   *py = y;
   if (req_comp == 0) req_comp = *comp;
   result=convert_format(result,4,req_comp,x,y);

   return result;
}