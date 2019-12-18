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
typedef  int u8 ;

/* Variables and functions */

int sqlite3Fts5UnicodeCatParse(const char *zCat, u8 *aArray){ 
  aArray[0] = 1;
  switch( zCat[0] ){
    case 'C':
          switch( zCat[1] ){
            case 'c': aArray[1] = 1; break;
            case 'f': aArray[2] = 1; break;
            case 'n': aArray[3] = 1; break;
            case 's': aArray[4] = 1; break;
            case 'o': aArray[31] = 1; break;
            case '*': 
              aArray[1] = 1;
              aArray[2] = 1;
              aArray[3] = 1;
              aArray[4] = 1;
              aArray[31] = 1;
              break;
            default: return 1;          }
          break;

    case 'L':
          switch( zCat[1] ){
            case 'l': aArray[5] = 1; break;
            case 'm': aArray[6] = 1; break;
            case 'o': aArray[7] = 1; break;
            case 't': aArray[8] = 1; break;
            case 'u': aArray[9] = 1; break;
            case 'C': aArray[30] = 1; break;
            case '*': 
              aArray[5] = 1;
              aArray[6] = 1;
              aArray[7] = 1;
              aArray[8] = 1;
              aArray[9] = 1;
              aArray[30] = 1;
              break;
            default: return 1;          }
          break;

    case 'M':
          switch( zCat[1] ){
            case 'c': aArray[10] = 1; break;
            case 'e': aArray[11] = 1; break;
            case 'n': aArray[12] = 1; break;
            case '*': 
              aArray[10] = 1;
              aArray[11] = 1;
              aArray[12] = 1;
              break;
            default: return 1;          }
          break;

    case 'N':
          switch( zCat[1] ){
            case 'd': aArray[13] = 1; break;
            case 'l': aArray[14] = 1; break;
            case 'o': aArray[15] = 1; break;
            case '*': 
              aArray[13] = 1;
              aArray[14] = 1;
              aArray[15] = 1;
              break;
            default: return 1;          }
          break;

    case 'P':
          switch( zCat[1] ){
            case 'c': aArray[16] = 1; break;
            case 'd': aArray[17] = 1; break;
            case 'e': aArray[18] = 1; break;
            case 'f': aArray[19] = 1; break;
            case 'i': aArray[20] = 1; break;
            case 'o': aArray[21] = 1; break;
            case 's': aArray[22] = 1; break;
            case '*': 
              aArray[16] = 1;
              aArray[17] = 1;
              aArray[18] = 1;
              aArray[19] = 1;
              aArray[20] = 1;
              aArray[21] = 1;
              aArray[22] = 1;
              break;
            default: return 1;          }
          break;

    case 'S':
          switch( zCat[1] ){
            case 'c': aArray[23] = 1; break;
            case 'k': aArray[24] = 1; break;
            case 'm': aArray[25] = 1; break;
            case 'o': aArray[26] = 1; break;
            case '*': 
              aArray[23] = 1;
              aArray[24] = 1;
              aArray[25] = 1;
              aArray[26] = 1;
              break;
            default: return 1;          }
          break;

    case 'Z':
          switch( zCat[1] ){
            case 'l': aArray[27] = 1; break;
            case 'p': aArray[28] = 1; break;
            case 's': aArray[29] = 1; break;
            case '*': 
              aArray[27] = 1;
              aArray[28] = 1;
              aArray[29] = 1;
              break;
            default: return 1;          }
          break;

  }
  return 0;
}