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
typedef  scalar_t__ GLint ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 

__attribute__((used)) static GLboolean isLegalLevels(GLint userLevel,GLint baseLevel,GLint maxLevel,
			       GLint totalLevels)
{
   if (baseLevel < 0 || baseLevel < userLevel || maxLevel < baseLevel ||
       totalLevels < maxLevel)
      return GL_FALSE;
   else return GL_TRUE;
}