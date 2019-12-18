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
typedef  int /*<<< orphan*/  StringBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  append (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void appendList(StringBuffer *sb, int nString, char **azString){
  int i;
  for(i=0; i<nString; ++i){
    if( i>0 ) append(sb, ", ");
    append(sb, azString[i]);
  }
}