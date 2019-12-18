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
typedef  int /*<<< orphan*/  SDL_Event ;

/* Variables and functions */
 scalar_t__ IsDebuggerPresent () ; 
 int /*<<< orphan*/  SDL_CreateWindow (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SDL_GL_BLUE_SIZE ; 
 int SDL_GL_CONTEXT_DEBUG_FLAG ; 
 int /*<<< orphan*/  SDL_GL_CONTEXT_FLAGS ; 
 int /*<<< orphan*/  SDL_GL_CONTEXT_MAJOR_VERSION ; 
 int /*<<< orphan*/  SDL_GL_CONTEXT_MINOR_VERSION ; 
 int SDL_GL_CONTEXT_PROFILE_COMPATIBILITY ; 
 int /*<<< orphan*/  SDL_GL_CONTEXT_PROFILE_MASK ; 
 int /*<<< orphan*/  SDL_GL_CreateContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_GL_DEPTH_SIZE ; 
 int /*<<< orphan*/  SDL_GL_GREEN_SIZE ; 
 int /*<<< orphan*/  SDL_GL_MULTISAMPLESAMPLES ; 
 int /*<<< orphan*/  SDL_GL_MakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_GL_RED_SIZE ; 
 int /*<<< orphan*/  SDL_GL_SetAttribute (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDL_GL_SetSwapInterval (int) ; 
 int /*<<< orphan*/  SDL_HINT_MOUSE_RELATIVE_MODE_WARP ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 scalar_t__ SDL_PollEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_SetHint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SDL_SetRelativeMouseMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_TRUE ; 
 int /*<<< orphan*/  SDL_WINDOWPOS_UNDEFINED ; 
 int SDL_WINDOW_OPENGL ; 
 int SDL_WINDOW_RESIZABLE ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  enable_synchronous () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  getTimestep (float) ; 
 int /*<<< orphan*/  glDebugMessageCallbackARB (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_debug ; 
 int initialized ; 
 int /*<<< orphan*/  loopmode (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mesh_init () ; 
 int /*<<< orphan*/  prepare_threads () ; 
 int /*<<< orphan*/  process_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quit ; 
 int /*<<< orphan*/  render_init () ; 
 int screen_x ; 
 int screen_y ; 
 int /*<<< orphan*/  stbgl_initExtensions () ; 
 int /*<<< orphan*/  window ; 
 int /*<<< orphan*/  world_init () ; 

int SDL_main(int argc, char **argv)
{
   SDL_Init(SDL_INIT_VIDEO);

   prepare_threads();

   SDL_GL_SetAttribute(SDL_GL_RED_SIZE  , 8);
   SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE , 8);
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

   #ifdef GL_DEBUG
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
   #endif

   SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

   screen_x = 1920;
   screen_y = 1080;

   window = SDL_CreateWindow("caveview", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   screen_x, screen_y,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
                             );
   if (!window) error("Couldn't create window");

   context = SDL_GL_CreateContext(window);
   if (!context) error("Couldn't create context");

   SDL_GL_MakeCurrent(window, context); // is this true by default?

   SDL_SetRelativeMouseMode(SDL_TRUE);
   #if defined(_MSC_VER) && _MSC_VER < 1300
   // work around broken behavior in VC6 debugging
   if (IsDebuggerPresent())
      SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1");
   #endif

   stbgl_initExtensions();

   #ifdef GL_DEBUG
   if (glDebugMessageCallbackARB) {
      glDebugMessageCallbackARB(gl_debug, NULL);

      enable_synchronous();
   }
   #endif

   SDL_GL_SetSwapInterval(1);

   render_init();
   mesh_init();
   world_init();

   initialized = 1;

   while (!quit) {
      SDL_Event e;
      while (SDL_PollEvent(&e))
         process_event(&e);

      loopmode(getTimestep(0.0166f/8), 1, 1);
   }

   return 0;
}