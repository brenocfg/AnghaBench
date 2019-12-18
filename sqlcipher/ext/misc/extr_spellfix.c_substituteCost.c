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
 char CCLASS_B ; 
 char CCLASS_Y ; 
 char characterClass (char,char) ; 

__attribute__((used)) static int substituteCost(char cPrev, char cFrom, char cTo){
  char classFrom, classTo;
  if( cFrom==cTo ){
    /* Exact match */
    return 0;
  }
  if( cFrom==(cTo^0x20) && ((cTo>='A' && cTo<='Z') || (cTo>='a' && cTo<='z')) ){
    /* differ only in case */
    return 0;
  }
  classFrom = characterClass(cPrev, cFrom);
  classTo = characterClass(cPrev, cTo);
  if( classFrom==classTo ){
    /* Same character class */
    return 40;
  }
  if( classFrom>=CCLASS_B && classFrom<=CCLASS_Y
      && classTo>=CCLASS_B && classTo<=CCLASS_Y ){
    /* Convert from one consonant to another, but in a different class */
    return 75;
  }
  /* Any other subsitution */
  return 100;
}