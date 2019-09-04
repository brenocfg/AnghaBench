#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int is_corner; int num_vary_x; int num_vary_y; void** num_color; void* short_side_len; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ stbhw_config ;

/* Variables and functions */
 void* atoi (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 char* stbhw_get_last_error () ; 
 int /*<<< orphan*/  stbhw_get_template_size (TYPE_1__*,int*,int*) ; 
 scalar_t__ stbhw_make_template (TYPE_1__*,unsigned char*,int,int,int) ; 
 int /*<<< orphan*/  stbi_write_png (char*,int,int,int,unsigned char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
   stbhw_config c = { 0 };
   int w,h, num_colors,i;
   unsigned char *data;

   if (argc == 1)  goto usage;
   if (argc  < 3)  goto error;

   switch (argv[2][0]) {
      case 'c':
         if (argc <  8 || argc > 10)
            goto error;
         num_colors = 4;
         c.is_corner = 1;
         break;

      case 'e':
         if (argc < 10 || argc > 12)
            goto error;
         num_colors = 6;
         c.is_corner = 0;
         break;

      default:
         goto error;
   }

   c.short_side_len = atoi(argv[3]);
   for (i=0; i < num_colors; ++i)
      c.num_color[i] = atoi(argv[4+i]);

   c.num_vary_x = 1;
   c.num_vary_y = 1;

   if (argc > 4+i)
      c.num_vary_x = atoi(argv[4+i]);
   if (argc > 5+i)
      c.num_vary_y = atoi(argv[5+i]);

   stbhw_get_template_size(&c, &w, &h);

   data = (unsigned char *) malloc(w*h*3);

   if (stbhw_make_template(&c, data, w, h, w*3))
      stbi_write_png(argv[1], w, h, 3, data, w*3);
   else
      fprintf(stderr, "Error: %s\n", stbhw_get_last_error());
   return 0;

 error:
   fputs("Invalid command-line arguments\n\n", stderr);
 usage:
   fputs("Usage (see source for corner & edge type definitions):\n\n", stderr);
   fputs("herringbone_generator {outfile} c {sidelen} {c0} {c1} {c2} {c3} [{vx} {vy}]\n"
         "     {outfile}  -- filename that template will be written to as PNG\n"
         "     {sidelen}  -- length of short side of rectangle in pixels\n"
         "     {c0}       -- number of colors for corner type 0\n"
         "     {c1}       -- number of colors for corner type 1\n"
         "     {c2}       -- number of colors for corner type 2\n"
         "     {c3}       -- number of colors for corner type 3\n"
         "     {vx}       -- number of color-duplicating variations horizontally in template\n"
         "     {vy}       -- number of color-duplicating variations vertically in template\n"
         "\n"
         , stderr);
   fputs("herringbone_generator {outfile} e {sidelen} {e0} {e1} {e2} {e3} {e4} {e5} [{vx} {vy}]\n"
         "     {outfile}  -- filename that template will be written to as PNG\n"
         "     {sidelen}  -- length of short side of rectangle in pixels\n"
         "     {e0}       -- number of colors for edge type 0\n"
         "     {e1}       -- number of colors for edge type 1\n"
         "     {e2}       -- number of colors for edge type 2\n"
         "     {e3}       -- number of colors for edge type 3\n"
         "     {e4}       -- number of colors for edge type 4\n"
         "     {e5}       -- number of colors for edge type 5\n"
         "     {vx}       -- number of color-duplicating variations horizontally in template\n"
         "     {vy}       -- number of color-duplicating variations vertically in template\n"
         , stderr);
   return 1;
}