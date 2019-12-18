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
struct TYPE_4__ {int type; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  key; int /*<<< orphan*/  my; int /*<<< orphan*/  mx; } ;
typedef  TYPE_1__ stbwingraph_event ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FRAMEBUFFER_SRGB_EXT ; 
#define  STBWGE_char 139 
#define  STBWGE_create 138 
#define  STBWGE_draw 137 
#define  STBWGE_keydown 136 
#define  STBWGE_keyup 135 
#define  STBWGE_leftdown 134 
#define  STBWGE_leftup 133 
#define  STBWGE_mousemove 132 
#define  STBWGE_mousewheel 131 
#define  STBWGE_rightdown 130 
#define  STBWGE_rightup 129 
#define  STBWGE_size 128 
 int STBWINGRAPH_unprocessed ; 
 int STBWINGRAPH_winproc_exit ; 
 int /*<<< orphan*/  VK_DOWN ; 
 int /*<<< orphan*/  VK_LEFT ; 
 int /*<<< orphan*/  VK_RIGHT ; 
 int /*<<< orphan*/  VK_UP ; 
 int black_on_white ; 
 int /*<<< orphan*/  do_mouse (TYPE_1__*,int,int) ; 
 int font ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialized ; 
 int integer_align ; 
 int /*<<< orphan*/  loopmode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int* move ; 
 int /*<<< orphan*/  raw_mouse_x ; 
 int /*<<< orphan*/  raw_mouse_y ; 
 int /*<<< orphan*/  rotate_t ; 
 int rotating ; 
 int show_tex ; 
 int srgb ; 
 int /*<<< orphan*/  stbwingraph_ShowCursor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sx ; 
 int /*<<< orphan*/  sy ; 
 int /*<<< orphan*/  translate_t ; 
 int translating ; 

int winproc(void *data, stbwingraph_event *e)
{
   switch (e->type) {
      case STBWGE_create:
         break;

      case STBWGE_char:
         switch(e->key) {
            case 27:
               stbwingraph_ShowCursor(NULL,1);
               return STBWINGRAPH_winproc_exit;
               break;
            case 'o': case 'O':
               font = (font+1) % 3 + (font/3)*3;
               break;
            case 's': case 'S':
               font = (font+3) % 6;
               break;
            case 't': case 'T':
               translating = !translating;
               translate_t = 0;
               break;
            case 'r': case 'R':
               rotating = !rotating;
               rotate_t = 0;
               break;
            case 'p': case 'P':
               integer_align = !integer_align;
               break;
            case 'g': case 'G':
               srgb = !srgb;
               if (srgb)
                  glEnable(GL_FRAMEBUFFER_SRGB_EXT);
               else
                  glDisable(GL_FRAMEBUFFER_SRGB_EXT);
               break;
            case 'v': case 'V':
               show_tex = !show_tex;
               break;
            case 'b': case 'B':
               black_on_white = !black_on_white;
               break;
         }
         break;

      case STBWGE_mousemove:
         raw_mouse_x = e->mx;
         raw_mouse_y = e->my;
         break;

#if 0
      case STBWGE_mousewheel:  do_mouse(e,0,0); break;
      case STBWGE_leftdown:    do_mouse(e, 1,0); break;
      case STBWGE_leftup:      do_mouse(e,-1,0); break;
      case STBWGE_rightdown:   do_mouse(e,0, 1); break;
      case STBWGE_rightup:     do_mouse(e,0,-1); break;
#endif

      case STBWGE_keydown:
         if (e->key == VK_RIGHT) move[0] = 1;
         if (e->key == VK_LEFT)  move[1] = 1;
         if (e->key == VK_UP)    move[2] = 1;
         if (e->key == VK_DOWN)  move[3] = 1;
         break;
      case STBWGE_keyup:
         if (e->key == VK_RIGHT) move[0] = 0;
         if (e->key == VK_LEFT)  move[1] = 0;
         if (e->key == VK_UP)    move[2] = 0;
         if (e->key == VK_DOWN)  move[3] = 0;
         break;

      case STBWGE_size:
         sx = e->width;
         sy = e->height;
         loopmode(0,1,0);
         break;

      case STBWGE_draw:
         if (initialized)
            loopmode(0,1,0);
         break;

      default:
         return STBWINGRAPH_unprocessed;
   }
   return 0;
}