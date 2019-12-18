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
 char CCLASS_SILENT ; 
 char CCLASS_VOWEL ; 
 char characterClass (char,char) ; 

__attribute__((used)) static int insertOrDeleteCost(char cPrev, char c, char cNext){
  char classC = characterClass(cPrev, c);
  char classCprev;

  if( classC==CCLASS_SILENT ){
    /* Insert or delete "silent" characters such as H or W */
    return 1;
  }
  if( cPrev==c ){
    /* Repeated characters, or miss a repeat */
    return 10;
  }
  if( classC==CCLASS_VOWEL && (cPrev=='r' || cNext=='r') ){
    return 20;  /* Insert a vowel before or after 'r' */
  }
  classCprev = characterClass(cPrev, cPrev);
  if( classC==classCprev ){
    if( classC==CCLASS_VOWEL ){
      /* Remove or add a new vowel to a vowel cluster */
      return 15;
    }else{
      /* Remove or add a consonant not in the same class */
      return 50;
    }
  }

  /* any other character insertion or deletion */
  return 100;
}