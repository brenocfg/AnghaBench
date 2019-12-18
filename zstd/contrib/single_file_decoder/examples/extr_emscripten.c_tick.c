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

/* Variables and functions */
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_UNSIGNED_SHORT ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glDrawElements (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFlush () ; 
 int /*<<< orphan*/  glUniform1f (scalar_t__,float) ; 
 float rotDeg ; 
 scalar_t__ uRotId ; 

__attribute__((used)) static void tick() {
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (uRotId >= 0) {
		glUniform1f(uRotId, rotDeg);
		rotDeg += 0.1f;
		if (rotDeg >= 360.0f) {
			rotDeg -= 360.0f;
		}
	}

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glFlush();
}