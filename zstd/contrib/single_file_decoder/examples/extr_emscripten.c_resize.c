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
typedef  int /*<<< orphan*/  EmscriptenUiEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 scalar_t__ EMSCRIPTEN_RESULT_SUCCESS ; 
 int /*<<< orphan*/  EM_FALSE ; 
 scalar_t__ emscripten_get_element_css_size (char*,double*,double*) ; 
 int /*<<< orphan*/  emscripten_set_canvas_element_size (char*,double,double) ; 
 scalar_t__ glCtx ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static EM_BOOL resize(int type, const EmscriptenUiEvent* e, void* data) {
	double surfaceW;
	double surfaceH;
	if (emscripten_get_element_css_size   ("#canvas", &surfaceW, &surfaceH) == EMSCRIPTEN_RESULT_SUCCESS) {
		emscripten_set_canvas_element_size("#canvas",  surfaceW,  surfaceH);
		if (glCtx) {
			glViewport(0, 0, (int) surfaceW, (int) surfaceH);
		}
	}
	(void) type;
	(void) data;
	(void) e;
	return EM_FALSE;
}