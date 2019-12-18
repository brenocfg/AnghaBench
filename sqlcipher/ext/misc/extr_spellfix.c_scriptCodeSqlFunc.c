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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 scalar_t__ CCLASS_DIGIT ; 
#define  SCRIPT_ARABIC 132 
#define  SCRIPT_CYRILLIC 131 
#define  SCRIPT_GREEK 130 
#define  SCRIPT_HEBREW 129 
#define  SCRIPT_LATIN 128 
 scalar_t__* midClass ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 unsigned char* sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int utf8Read (unsigned char const*,int,int*) ; 

__attribute__((used)) static void scriptCodeSqlFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  const unsigned char *zIn = sqlite3_value_text(argv[0]);
  int nIn = sqlite3_value_bytes(argv[0]);
  int c, sz;
  int scriptMask = 0;
  int res;
  int seenDigit = 0;
# define SCRIPT_LATIN       0x0001
# define SCRIPT_CYRILLIC    0x0002
# define SCRIPT_GREEK       0x0004
# define SCRIPT_HEBREW      0x0008
# define SCRIPT_ARABIC      0x0010

  while( nIn>0 ){
    c = utf8Read(zIn, nIn, &sz);
    zIn += sz;
    nIn -= sz;
    if( c<0x02af ){
      if( c>=0x80 || midClass[c&0x7f]<CCLASS_DIGIT ){
        scriptMask |= SCRIPT_LATIN;
      }else if( c>='0' && c<='9' ){
        seenDigit = 1;
      }
    }else if( c>=0x0400 && c<=0x04ff ){
      scriptMask |= SCRIPT_CYRILLIC;
    }else if( c>=0x0386 && c<=0x03ce ){
      scriptMask |= SCRIPT_GREEK;
    }else if( c>=0x0590 && c<=0x05ff ){
      scriptMask |= SCRIPT_HEBREW;
    }else if( c>=0x0600 && c<=0x06ff ){
      scriptMask |= SCRIPT_ARABIC;
    }
  }
  if( scriptMask==0 && seenDigit ) scriptMask = SCRIPT_LATIN;
  switch( scriptMask ){
    case 0:                res = 999; break;
    case SCRIPT_LATIN:     res = 215; break;
    case SCRIPT_CYRILLIC:  res = 220; break;
    case SCRIPT_GREEK:     res = 200; break;
    case SCRIPT_HEBREW:    res = 125; break;
    case SCRIPT_ARABIC:    res = 160; break;
    default:               res = 998; break;
  }
  sqlite3_result_int(context, res);
}