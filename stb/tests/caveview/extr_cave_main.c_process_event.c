#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int sym; int scancode; int mod; } ;
struct TYPE_9__ {TYPE_2__ keysym; } ;
struct TYPE_7__ {int /*<<< orphan*/  data2; int /*<<< orphan*/  data1; int /*<<< orphan*/  event; } ;
struct TYPE_10__ {int type; TYPE_3__ key; TYPE_1__ window; } ;
typedef  int /*<<< orphan*/  SDL_Keymod ;
typedef  TYPE_4__ SDL_Event ;

/* Variables and functions */
 int /*<<< orphan*/  GAME_editor ; 
 int KMOD_CTRL ; 
#define  SDLK_DOWN 151 
 int SDLK_ESCAPE ; 
#define  SDLK_LEFT 150 
#define  SDLK_RIGHT 149 
 int SDLK_SPACE ; 
#define  SDLK_UP 148 
 int /*<<< orphan*/  SDL_GetModState () ; 
#define  SDL_KEYDOWN 147 
#define  SDL_KEYUP 146 
#define  SDL_MOUSEBUTTONDOWN 145 
#define  SDL_MOUSEBUTTONUP 144 
#define  SDL_MOUSEMOTION 143 
#define  SDL_QUIT 142 
 int SDL_SCANCODE_A ; 
#define  SDL_SCANCODE_B 141 
#define  SDL_SCANCODE_C 140 
 int SDL_SCANCODE_D ; 
#define  SDL_SCANCODE_E 139 
#define  SDL_SCANCODE_G 138 
#define  SDL_SCANCODE_I 137 
#define  SDL_SCANCODE_L 136 
 int SDL_SCANCODE_LCTRL ; 
#define  SDL_SCANCODE_R 135 
#define  SDL_SCANCODE_S 134 
#define  SDL_SCANCODE_V 133 
 int SDL_SCANCODE_W ; 
#define  SDL_SCANCODE_X 132 
#define  SDL_SCANCODE_Y 131 
#define  SDL_SCANCODE_Z 130 
#define  SDL_WINDOWEVENT 129 
#define  SDL_WINDOWEVENT_SIZE_CHANGED 128 
 int /*<<< orphan*/  STBTE_act_copy ; 
 int /*<<< orphan*/  STBTE_act_cut ; 
 int /*<<< orphan*/  STBTE_act_paste ; 
 int /*<<< orphan*/  STBTE_act_redo ; 
 int /*<<< orphan*/  STBTE_act_toggle_grid ; 
 int /*<<< orphan*/  STBTE_act_undo ; 
 int /*<<< orphan*/  STBTE_scroll_down ; 
 int /*<<< orphan*/  STBTE_scroll_left ; 
 int /*<<< orphan*/  STBTE_scroll_right ; 
 int /*<<< orphan*/  STBTE_scroll_up ; 
 int /*<<< orphan*/  STBTE_tool_brush ; 
 int /*<<< orphan*/  STBTE_tool_erase ; 
 int /*<<< orphan*/  STBTE_tool_eyedropper ; 
 int /*<<< orphan*/  STBTE_tool_link ; 
 int /*<<< orphan*/  STBTE_tool_rectangle ; 
 int /*<<< orphan*/  STBTE_tool_select ; 
 int /*<<< orphan*/  active_control_clear (int) ; 
 int /*<<< orphan*/  active_control_set (int) ; 
 int /*<<< orphan*/  editor_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  game_mode ; 
 int global_hack ; 
 int /*<<< orphan*/  loopmode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_sdl_mouse (TYPE_4__*) ; 
 int quit ; 
 int /*<<< orphan*/  screen_x ; 
 int /*<<< orphan*/  screen_y ; 

void process_event(SDL_Event *e)
{
   switch (e->type) {
      case SDL_MOUSEMOTION:
         process_sdl_mouse(e);
         break;
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
         break;

      case SDL_QUIT:
         quit = 1;
         break;

      case SDL_WINDOWEVENT:
         switch (e->window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
               screen_x = e->window.data1;
               screen_y = e->window.data2;
               loopmode(0,1,0);
               break;
         }
         break;

      case SDL_KEYDOWN: {
         int k = e->key.keysym.sym;
         int s = e->key.keysym.scancode;
         SDL_Keymod mod;
         mod = SDL_GetModState();
         if (k == SDLK_ESCAPE)
            quit = 1;

         if (s == SDL_SCANCODE_D)   active_control_set(0);
         if (s == SDL_SCANCODE_A)   active_control_set(1);
         if (s == SDL_SCANCODE_W)   active_control_set(2);
         if (s == SDL_SCANCODE_S)   active_control_set(3);
         if (k == SDLK_SPACE)       active_control_set(4); 
         if (s == SDL_SCANCODE_LCTRL)   active_control_set(5);
         if (s == SDL_SCANCODE_S)   active_control_set(6);
         if (s == SDL_SCANCODE_D)   active_control_set(7);
         if (k == '1') global_hack = !global_hack;
         if (k == '2') global_hack = -1;

         #if 0
         if (game_mode == GAME_editor) {
            switch (k) {
               case SDLK_RIGHT: editor_key(STBTE_scroll_right); break;
               case SDLK_LEFT : editor_key(STBTE_scroll_left ); break;
               case SDLK_UP   : editor_key(STBTE_scroll_up   ); break;
               case SDLK_DOWN : editor_key(STBTE_scroll_down ); break;
            }
            switch (s) {
               case SDL_SCANCODE_S: editor_key(STBTE_tool_select); break;
               case SDL_SCANCODE_B: editor_key(STBTE_tool_brush ); break;
               case SDL_SCANCODE_E: editor_key(STBTE_tool_erase ); break;
               case SDL_SCANCODE_R: editor_key(STBTE_tool_rectangle ); break;
               case SDL_SCANCODE_I: editor_key(STBTE_tool_eyedropper); break;
               case SDL_SCANCODE_L: editor_key(STBTE_tool_link); break;
               case SDL_SCANCODE_G: editor_key(STBTE_act_toggle_grid); break;
            }
            if ((e->key.keysym.mod & KMOD_CTRL) && !(e->key.keysym.mod & ~KMOD_CTRL)) {
               switch (s) {
                  case SDL_SCANCODE_X: editor_key(STBTE_act_cut  ); break;
                  case SDL_SCANCODE_C: editor_key(STBTE_act_copy ); break;
                  case SDL_SCANCODE_V: editor_key(STBTE_act_paste); break;
                  case SDL_SCANCODE_Z: editor_key(STBTE_act_undo ); break;
                  case SDL_SCANCODE_Y: editor_key(STBTE_act_redo ); break;
               }
            }
         }
         #endif
         break;
      }
      case SDL_KEYUP: {
         int k = e->key.keysym.sym;
         int s = e->key.keysym.scancode;
         if (s == SDL_SCANCODE_D)   active_control_clear(0);
         if (s == SDL_SCANCODE_A)   active_control_clear(1);
         if (s == SDL_SCANCODE_W)   active_control_clear(2);
         if (s == SDL_SCANCODE_S)   active_control_clear(3);
         if (k == SDLK_SPACE)       active_control_clear(4); 
         if (s == SDL_SCANCODE_LCTRL)   active_control_clear(5);
         if (s == SDL_SCANCODE_S)   active_control_clear(6);
         if (s == SDL_SCANCODE_D)   active_control_clear(7);
         break;
      }
   }
}