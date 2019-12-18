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
typedef  int /*<<< orphan*/  aDia ;

/* Variables and functions */
 unsigned char HIBIT ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int fts5_remove_diacritic(int c, int bComplex){
  unsigned short aDia[] = {
        0,  1797,  1848,  1859,  1891,  1928,  1940,  1995, 
     2024,  2040,  2060,  2110,  2168,  2206,  2264,  2286, 
     2344,  2383,  2472,  2488,  2516,  2596,  2668,  2732, 
     2782,  2842,  2894,  2954,  2984,  3000,  3028,  3336, 
     3456,  3696,  3712,  3728,  3744,  3766,  3832,  3896, 
     3912,  3928,  3944,  3968,  4008,  4040,  4056,  4106, 
     4138,  4170,  4202,  4234,  4266,  4296,  4312,  4344, 
     4408,  4424,  4442,  4472,  4488,  4504,  6148,  6198, 
     6264,  6280,  6360,  6429,  6505,  6529, 61448, 61468, 
    61512, 61534, 61592, 61610, 61642, 61672, 61688, 61704, 
    61726, 61784, 61800, 61816, 61836, 61880, 61896, 61914, 
    61948, 61998, 62062, 62122, 62154, 62184, 62200, 62218, 
    62252, 62302, 62364, 62410, 62442, 62478, 62536, 62554, 
    62584, 62604, 62640, 62648, 62656, 62664, 62730, 62766, 
    62830, 62890, 62924, 62974, 63032, 63050, 63082, 63118, 
    63182, 63242, 63274, 63310, 63368, 63390, 
  };
#define HIBIT ((unsigned char)0x80)
  unsigned char aChar[] = {
    '\0',      'a',       'c',       'e',       'i',       'n',       
    'o',       'u',       'y',       'y',       'a',       'c',       
    'd',       'e',       'e',       'g',       'h',       'i',       
    'j',       'k',       'l',       'n',       'o',       'r',       
    's',       't',       'u',       'u',       'w',       'y',       
    'z',       'o',       'u',       'a',       'i',       'o',       
    'u',       'u'|HIBIT, 'a'|HIBIT, 'g',       'k',       'o',       
    'o'|HIBIT, 'j',       'g',       'n',       'a'|HIBIT, 'a',       
    'e',       'i',       'o',       'r',       'u',       's',       
    't',       'h',       'a',       'e',       'o'|HIBIT, 'o',       
    'o'|HIBIT, 'y',       '\0',      '\0',      '\0',      '\0',      
    '\0',      '\0',      '\0',      '\0',      'a',       'b',       
    'c'|HIBIT, 'd',       'd',       'e'|HIBIT, 'e',       'e'|HIBIT, 
    'f',       'g',       'h',       'h',       'i',       'i'|HIBIT, 
    'k',       'l',       'l'|HIBIT, 'l',       'm',       'n',       
    'o'|HIBIT, 'p',       'r',       'r'|HIBIT, 'r',       's',       
    's'|HIBIT, 't',       'u',       'u'|HIBIT, 'v',       'w',       
    'w',       'x',       'y',       'z',       'h',       't',       
    'w',       'y',       'a',       'a'|HIBIT, 'a'|HIBIT, 'a'|HIBIT, 
    'e',       'e'|HIBIT, 'e'|HIBIT, 'i',       'o',       'o'|HIBIT, 
    'o'|HIBIT, 'o'|HIBIT, 'u',       'u'|HIBIT, 'u'|HIBIT, 'y',       
  };

  unsigned int key = (((unsigned int)c)<<3) | 0x00000007;
  int iRes = 0;
  int iHi = sizeof(aDia)/sizeof(aDia[0]) - 1;
  int iLo = 0;
  while( iHi>=iLo ){
    int iTest = (iHi + iLo) / 2;
    if( key >= aDia[iTest] ){
      iRes = iTest;
      iLo = iTest+1;
    }else{
      iHi = iTest-1;
    }
  }
  assert( key>=aDia[iRes] );
  if( bComplex==0 && (aChar[iRes] & 0x80) ) return c;
  return (c > (aDia[iRes]>>3) + (aDia[iRes]&0x07)) ? c : ((int)aChar[iRes] & 0x7F);
}