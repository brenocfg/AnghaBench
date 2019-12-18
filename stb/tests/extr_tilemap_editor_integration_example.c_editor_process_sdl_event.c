#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int mod; int /*<<< orphan*/  scancode; int /*<<< orphan*/  sym; } ;
struct TYPE_7__ {TYPE_1__ keysym; } ;
struct TYPE_8__ {int type; TYPE_2__ key; } ;
typedef  TYPE_3__ SDL_Event ;

/* Variables and functions */
 int KMOD_CTRL ; 
#define  SDLK_DOWN 148 
#define  SDLK_LEFT 147 
#define  SDLK_RIGHT 146 
#define  SDLK_UP 145 
#define  SDL_KEYDOWN 144 
#define  SDL_MOUSEBUTTONDOWN 143 
#define  SDL_MOUSEBUTTONUP 142 
#define  SDL_MOUSEMOTION 141 
#define  SDL_MOUSEWHEEL 140 
#define  SDL_SCANCODE_B 139 
#define  SDL_SCANCODE_C 138 
#define  SDL_SCANCODE_E 137 
#define  SDL_SCANCODE_G 136 
#define  SDL_SCANCODE_I 135 
#define  SDL_SCANCODE_L 134 
#define  SDL_SCANCODE_R 133 
#define  SDL_SCANCODE_S 132 
#define  SDL_SCANCODE_V 131 
#define  SDL_SCANCODE_X 130 
#define  SDL_SCANCODE_Y 129 
#define  SDL_SCANCODE_Z 128 
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
 int /*<<< orphan*/  edit_map ; 
 int /*<<< orphan*/  editor_key (int /*<<< orphan*/ ) ; 
 float editor_scale ; 
 int /*<<< orphan*/  in_editor ; 
 int /*<<< orphan*/  stbte_mouse_sdl (int /*<<< orphan*/ ,TYPE_3__*,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void editor_process_sdl_event(SDL_Event *e)
{
   switch (e->type) {
      case SDL_MOUSEMOTION:
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
      case SDL_MOUSEWHEEL:
         stbte_mouse_sdl(edit_map, e, 1.0f/editor_scale,1.0f/editor_scale,0,0);
         break;

      case SDL_KEYDOWN:
         if (in_editor) {
            switch (e->key.keysym.sym) {
               case SDLK_RIGHT: editor_key(STBTE_scroll_right); break;
               case SDLK_LEFT : editor_key(STBTE_scroll_left ); break;
               case SDLK_UP   : editor_key(STBTE_scroll_up   ); break;
               case SDLK_DOWN : editor_key(STBTE_scroll_down ); break;
            }
            switch (e->key.keysym.scancode) {
               case SDL_SCANCODE_S: editor_key(STBTE_tool_select); break;
               case SDL_SCANCODE_B: editor_key(STBTE_tool_brush ); break;
               case SDL_SCANCODE_E: editor_key(STBTE_tool_erase ); break;
               case SDL_SCANCODE_R: editor_key(STBTE_tool_rectangle ); break;
               case SDL_SCANCODE_I: editor_key(STBTE_tool_eyedropper); break;
               case SDL_SCANCODE_L: editor_key(STBTE_tool_link);       break;
               case SDL_SCANCODE_G: editor_key(STBTE_act_toggle_grid); break;
            }
            if ((e->key.keysym.mod & KMOD_CTRL) && !(e->key.keysym.mod & ~KMOD_CTRL)) {
               switch (e->key.keysym.scancode) {
                  case SDL_SCANCODE_X: editor_key(STBTE_act_cut  ); break;
                  case SDL_SCANCODE_C: editor_key(STBTE_act_copy ); break;
                  case SDL_SCANCODE_V: editor_key(STBTE_act_paste); break;
                  case SDL_SCANCODE_Z: editor_key(STBTE_act_undo ); break;
                  case SDL_SCANCODE_Y: editor_key(STBTE_act_redo ); break;
               }
            }
         }
         break;
   }
}