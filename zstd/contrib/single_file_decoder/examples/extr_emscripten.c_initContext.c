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
typedef  int /*<<< orphan*/  EmscriptenWebGLContextAttributes ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EMSCRIPTEN_EVENT_TARGET_DOCUMENT ; 
 int /*<<< orphan*/  EM_FALSE ; 
 int /*<<< orphan*/  EM_TRUE ; 
 int /*<<< orphan*/  emscripten_set_resize_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  emscripten_webgl_create_context (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emscripten_webgl_init_context_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emscripten_webgl_make_context_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCtx ; 
 int /*<<< orphan*/  resize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static EM_BOOL initContext() {
	// Default attributes
	EmscriptenWebGLContextAttributes attr;
	emscripten_webgl_init_context_attributes(&attr);
	if ((glCtx = emscripten_webgl_create_context("#canvas", &attr))) {
		// Bind the context and fire a resize to get the initial size
		emscripten_webgl_make_context_current(glCtx);
		emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, NULL, EM_FALSE, resize);
		resize(0, NULL, NULL);
		return EM_TRUE;
	}
	return EM_FALSE;
}