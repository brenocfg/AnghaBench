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
 int /*<<< orphan*/  fts5PorterIsVowel (char,int) ; 

__attribute__((used)) static int fts5PorterGobbleVC(char *zStem, int nStem, int bPrevCons){
  int i;
  int bCons = bPrevCons;

  /* Scan for a vowel */
  for(i=0; i<nStem; i++){
    if( 0==(bCons = !fts5PorterIsVowel(zStem[i], bCons)) ) break;
  }

  /* Scan for a consonent */
  for(i++; i<nStem; i++){
    if( (bCons = !fts5PorterIsVowel(zStem[i], bCons)) ) return i+1;
  }
  return 0;
}