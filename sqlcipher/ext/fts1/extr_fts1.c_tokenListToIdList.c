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
 int /*<<< orphan*/  dequoteString (char*) ; 
 scalar_t__ safe_isalnum (char) ; 

__attribute__((used)) static void tokenListToIdList(char **azIn){
  int i, j;
  if( azIn ){
    for(i=0, j=-1; azIn[i]; i++){
      if( safe_isalnum(azIn[i][0]) || azIn[i][1] ){
        dequoteString(azIn[i]);
        if( j>=0 ){
          azIn[j] = azIn[i];
        }
        j++;
      }
    }
    azIn[j] = 0;
  }
}