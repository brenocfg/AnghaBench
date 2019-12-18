#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  i; } ;
struct TYPE_12__ {unsigned int (* xNextChar ) (TYPE_2__*) ;int nState; int* aArg; TYPE_2__ sIn; } ;
typedef  TYPE_1__ ReCompiled ;

/* Variables and functions */
 int RE_OP_ANY ; 
 int RE_OP_ANYSTAR ; 
 int RE_OP_BOUNDARY ; 
 int RE_OP_CC_EXC ; 
 int RE_OP_CC_INC ; 
 int RE_OP_CC_RANGE ; 
 int RE_OP_CC_VALUE ; 
 int RE_OP_DIGIT ; 
 int RE_OP_FORK ; 
 int RE_OP_GOTO ; 
 int RE_OP_MATCH ; 
 int RE_OP_NOTDIGIT ; 
 int RE_OP_NOTSPACE ; 
 int RE_OP_NOTWORD ; 
 int RE_OP_SPACE ; 
 int RE_OP_WORD ; 
 char rePeek (TYPE_1__*) ; 
 int /*<<< orphan*/  re_append (TYPE_1__*,int,unsigned int) ; 
 int /*<<< orphan*/  re_copy (TYPE_1__*,int,int) ; 
 unsigned int re_esc_char (TYPE_1__*) ; 
 int /*<<< orphan*/  re_insert (TYPE_1__*,int,int,int) ; 
 char* re_subcompile_re (TYPE_1__*) ; 
 unsigned int stub1 (TYPE_2__*) ; 
 unsigned int stub2 (TYPE_2__*) ; 
 unsigned int stub3 (TYPE_2__*) ; 

__attribute__((used)) static const char *re_subcompile_string(ReCompiled *p){
  int iPrev = -1;
  int iStart;
  unsigned c;
  const char *zErr;
  while( (c = p->xNextChar(&p->sIn))!=0 ){
    iStart = p->nState;
    switch( c ){
      case '|':
      case '$': 
      case ')': {
        p->sIn.i--;
        return 0;
      }
      case '(': {
        zErr = re_subcompile_re(p);
        if( zErr ) return zErr;
        if( rePeek(p)!=')' ) return "unmatched '('";
        p->sIn.i++;
        break;
      }
      case '.': {
        if( rePeek(p)=='*' ){
          re_append(p, RE_OP_ANYSTAR, 0);
          p->sIn.i++;
        }else{ 
          re_append(p, RE_OP_ANY, 0);
        }
        break;
      }
      case '*': {
        if( iPrev<0 ) return "'*' without operand";
        re_insert(p, iPrev, RE_OP_GOTO, p->nState - iPrev + 1);
        re_append(p, RE_OP_FORK, iPrev - p->nState + 1);
        break;
      }
      case '+': {
        if( iPrev<0 ) return "'+' without operand";
        re_append(p, RE_OP_FORK, iPrev - p->nState);
        break;
      }
      case '?': {
        if( iPrev<0 ) return "'?' without operand";
        re_insert(p, iPrev, RE_OP_FORK, p->nState - iPrev+1);
        break;
      }
      case '{': {
        int m = 0, n = 0;
        int sz, j;
        if( iPrev<0 ) return "'{m,n}' without operand";
        while( (c=rePeek(p))>='0' && c<='9' ){ m = m*10 + c - '0'; p->sIn.i++; }
        n = m;
        if( c==',' ){
          p->sIn.i++;
          n = 0;
          while( (c=rePeek(p))>='0' && c<='9' ){ n = n*10 + c-'0'; p->sIn.i++; }
        }
        if( c!='}' ) return "unmatched '{'";
        if( n>0 && n<m ) return "n less than m in '{m,n}'";
        p->sIn.i++;
        sz = p->nState - iPrev;
        if( m==0 ){
          if( n==0 ) return "both m and n are zero in '{m,n}'";
          re_insert(p, iPrev, RE_OP_FORK, sz+1);
          n--;
        }else{
          for(j=1; j<m; j++) re_copy(p, iPrev, sz);
        }
        for(j=m; j<n; j++){
          re_append(p, RE_OP_FORK, sz+1);
          re_copy(p, iPrev, sz);
        }
        if( n==0 && m>0 ){
          re_append(p, RE_OP_FORK, -sz);
        }
        break;
      }
      case '[': {
        int iFirst = p->nState;
        if( rePeek(p)=='^' ){
          re_append(p, RE_OP_CC_EXC, 0);
          p->sIn.i++;
        }else{
          re_append(p, RE_OP_CC_INC, 0);
        }
        while( (c = p->xNextChar(&p->sIn))!=0 ){
          if( c=='[' && rePeek(p)==':' ){
            return "POSIX character classes not supported";
          }
          if( c=='\\' ) c = re_esc_char(p);
          if( rePeek(p)=='-' ){
            re_append(p, RE_OP_CC_RANGE, c);
            p->sIn.i++;
            c = p->xNextChar(&p->sIn);
            if( c=='\\' ) c = re_esc_char(p);
            re_append(p, RE_OP_CC_RANGE, c);
          }else{
            re_append(p, RE_OP_CC_VALUE, c);
          }
          if( rePeek(p)==']' ){ p->sIn.i++; break; }
        }
        if( c==0 ) return "unclosed '['";
        p->aArg[iFirst] = p->nState - iFirst;
        break;
      }
      case '\\': {
        int specialOp = 0;
        switch( rePeek(p) ){
          case 'b': specialOp = RE_OP_BOUNDARY;   break;
          case 'd': specialOp = RE_OP_DIGIT;      break;
          case 'D': specialOp = RE_OP_NOTDIGIT;   break;
          case 's': specialOp = RE_OP_SPACE;      break;
          case 'S': specialOp = RE_OP_NOTSPACE;   break;
          case 'w': specialOp = RE_OP_WORD;       break;
          case 'W': specialOp = RE_OP_NOTWORD;    break;
        }
        if( specialOp ){
          p->sIn.i++;
          re_append(p, specialOp, 0);
        }else{
          c = re_esc_char(p);
          re_append(p, RE_OP_MATCH, c);
        }
        break;
      }
      default: {
        re_append(p, RE_OP_MATCH, c);
        break;
      }
    }
    iPrev = iStart;
  }
  return 0;
}