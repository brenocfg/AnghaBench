#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
struct TYPE_6__ {scalar_t__ eType; int jnFlags; size_t n; } ;
struct TYPE_5__ {char* zJson; scalar_t__ iDepth; size_t nNode; TYPE_2__* aNode; scalar_t__ oom; } ;
typedef  TYPE_1__ JsonParse ;
typedef  TYPE_2__ JsonNode ;

/* Variables and functions */
 int JNODE_ESCAPE ; 
 int JNODE_LABEL ; 
 scalar_t__ JSON_ARRAY ; 
 scalar_t__ JSON_FALSE ; 
 scalar_t__ JSON_INT ; 
 scalar_t__ JSON_MAX_DEPTH ; 
 scalar_t__ JSON_NULL ; 
 scalar_t__ JSON_OBJECT ; 
 scalar_t__ JSON_REAL ; 
 scalar_t__ JSON_STRING ; 
 scalar_t__ JSON_TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ jsonIs4Hex (char const*) ; 
 int jsonParseAddNode (TYPE_1__*,scalar_t__,size_t,char const*) ; 
 int /*<<< orphan*/  safe_isalnum (char const) ; 
 scalar_t__ safe_isspace (char const) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int jsonParseValue(JsonParse *pParse, u32 i){
  char c;
  u32 j;
  int iThis;
  int x;
  JsonNode *pNode;
  const char *z = pParse->zJson;
  while( safe_isspace(z[i]) ){ i++; }
  if( (c = z[i])=='{' ){
    /* Parse object */
    iThis = jsonParseAddNode(pParse, JSON_OBJECT, 0, 0);
    if( iThis<0 ) return -1;
    for(j=i+1;;j++){
      while( safe_isspace(z[j]) ){ j++; }
      if( ++pParse->iDepth > JSON_MAX_DEPTH ) return -1;
      x = jsonParseValue(pParse, j);
      if( x<0 ){
        pParse->iDepth--;
        if( x==(-2) && pParse->nNode==(u32)iThis+1 ) return j+1;
        return -1;
      }
      if( pParse->oom ) return -1;
      pNode = &pParse->aNode[pParse->nNode-1];
      if( pNode->eType!=JSON_STRING ) return -1;
      pNode->jnFlags |= JNODE_LABEL;
      j = x;
      while( safe_isspace(z[j]) ){ j++; }
      if( z[j]!=':' ) return -1;
      j++;
      x = jsonParseValue(pParse, j);
      pParse->iDepth--;
      if( x<0 ) return -1;
      j = x;
      while( safe_isspace(z[j]) ){ j++; }
      c = z[j];
      if( c==',' ) continue;
      if( c!='}' ) return -1;
      break;
    }
    pParse->aNode[iThis].n = pParse->nNode - (u32)iThis - 1;
    return j+1;
  }else if( c=='[' ){
    /* Parse array */
    iThis = jsonParseAddNode(pParse, JSON_ARRAY, 0, 0);
    if( iThis<0 ) return -1;
    for(j=i+1;;j++){
      while( safe_isspace(z[j]) ){ j++; }
      if( ++pParse->iDepth > JSON_MAX_DEPTH ) return -1;
      x = jsonParseValue(pParse, j);
      pParse->iDepth--;
      if( x<0 ){
        if( x==(-3) && pParse->nNode==(u32)iThis+1 ) return j+1;
        return -1;
      }
      j = x;
      while( safe_isspace(z[j]) ){ j++; }
      c = z[j];
      if( c==',' ) continue;
      if( c!=']' ) return -1;
      break;
    }
    pParse->aNode[iThis].n = pParse->nNode - (u32)iThis - 1;
    return j+1;
  }else if( c=='"' ){
    /* Parse string */
    u8 jnFlags = 0;
    j = i+1;
    for(;;){
      c = z[j];
      if( (c & ~0x1f)==0 ){
        /* Control characters are not allowed in strings */
        return -1;
      }
      if( c=='\\' ){
        c = z[++j];
        if( c=='"' || c=='\\' || c=='/' || c=='b' || c=='f'
           || c=='n' || c=='r' || c=='t'
           || (c=='u' && jsonIs4Hex(z+j+1)) ){
          jnFlags = JNODE_ESCAPE;
        }else{
          return -1;
        }
      }else if( c=='"' ){
        break;
      }
      j++;
    }
    jsonParseAddNode(pParse, JSON_STRING, j+1-i, &z[i]);
    if( !pParse->oom ) pParse->aNode[pParse->nNode-1].jnFlags = jnFlags;
    return j+1;
  }else if( c=='n'
         && strncmp(z+i,"null",4)==0
         && !safe_isalnum(z[i+4]) ){
    jsonParseAddNode(pParse, JSON_NULL, 0, 0);
    return i+4;
  }else if( c=='t'
         && strncmp(z+i,"true",4)==0
         && !safe_isalnum(z[i+4]) ){
    jsonParseAddNode(pParse, JSON_TRUE, 0, 0);
    return i+4;
  }else if( c=='f'
         && strncmp(z+i,"false",5)==0
         && !safe_isalnum(z[i+5]) ){
    jsonParseAddNode(pParse, JSON_FALSE, 0, 0);
    return i+5;
  }else if( c=='-' || (c>='0' && c<='9') ){
    /* Parse number */
    u8 seenDP = 0;
    u8 seenE = 0;
    assert( '-' < '0' );
    if( c<='0' ){
      j = c=='-' ? i+1 : i;
      if( z[j]=='0' && z[j+1]>='0' && z[j+1]<='9' ) return -1;
    }
    j = i+1;
    for(;; j++){
      c = z[j];
      if( c>='0' && c<='9' ) continue;
      if( c=='.' ){
        if( z[j-1]=='-' ) return -1;
        if( seenDP ) return -1;
        seenDP = 1;
        continue;
      }
      if( c=='e' || c=='E' ){
        if( z[j-1]<'0' ) return -1;
        if( seenE ) return -1;
        seenDP = seenE = 1;
        c = z[j+1];
        if( c=='+' || c=='-' ){
          j++;
          c = z[j+1];
        }
        if( c<'0' || c>'9' ) return -1;
        continue;
      }
      break;
    }
    if( z[j-1]<'0' ) return -1;
    jsonParseAddNode(pParse, seenDP ? JSON_REAL : JSON_INT,
                        j - i, &z[i]);
    return j;
  }else if( c=='}' ){
    return -2;  /* End of {...} */
  }else if( c==']' ){
    return -3;  /* End of [...] */
  }else if( c==0 ){
    return 0;   /* End of file */
  }else{
    return -1;  /* Syntax error */
  }
}