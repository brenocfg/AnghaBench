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
typedef  int /*<<< orphan*/  String ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (char**) ; 
 int /*<<< orphan*/  stringAppendTerm (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int evalCallback(void *pCData, int argc, char **argv, char **azCol){
  String *p = (String*)pCData;
  int i;
  UNUSED_PARAMETER(azCol);
  for(i=0; i<argc; i++) stringAppendTerm(p, argv[i]);
  return 0;
}