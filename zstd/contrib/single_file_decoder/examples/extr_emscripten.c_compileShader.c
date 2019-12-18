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
typedef  scalar_t__ GLuint ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  char GLchar ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COMPILE_STATUS ; 
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glCompileShader (scalar_t__) ; 
 scalar_t__ glCreateShader (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  glDeleteShader (scalar_t__) ; 
 int /*<<< orphan*/  glGetShaderInfoLog (scalar_t__,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetShaderiv (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glShaderSource (scalar_t__,int,char const**,int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static GLuint compileShader(GLenum const type, const GLchar* text) {
	GLuint shader = glCreateShader(type);
	if (shader) {
		glShaderSource (shader, 1, &text, NULL);
		glCompileShader(shader);
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (compiled) {
			return shader;
		} else {
			GLint logLen;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
			if (logLen > 1) {
				GLchar*  logStr = malloc(logLen);
				glGetShaderInfoLog(shader, logLen, NULL, logStr);
			#ifndef NDEBUG
				printf("Shader compilation error: %s\n", logStr);
			#endif
				free(logStr);
			}
			glDeleteShader(shader);
		}
	}
	return 0;
}