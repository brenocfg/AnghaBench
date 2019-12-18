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
 int /*<<< orphan*/  fts5PorterGobbleVC (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5Porter_MGt0(char *zStem, int nStem){
  return !!fts5PorterGobbleVC(zStem, nStem, 0);
}