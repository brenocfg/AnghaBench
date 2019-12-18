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
typedef  int /*<<< orphan*/  mStack ;
typedef  int /*<<< orphan*/  m ;

/* Variables and functions */
 int FINAL_INS_COST_DIV ; 
 int /*<<< orphan*/  assert (int) ; 
 int insertOrDeleteCost (char,char,char const) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sqlite3_free (int*) ; 
 int* sqlite3_malloc64 (int) ; 
 int substituteCost (char,char,char) ; 

__attribute__((used)) static int editdist1(const char *zA, const char *zB, int *pnMatch){
  int nA, nB;            /* Number of characters in zA[] and zB[] */
  int xA, xB;            /* Loop counters for zA[] and zB[] */
  char cA = 0, cB;       /* Current character of zA and zB */
  char cAprev, cBprev;   /* Previous character of zA and zB */
  char cAnext, cBnext;   /* Next character in zA and zB */
  int d;                 /* North-west cost value */
  int dc = 0;            /* North-west character value */
  int res;               /* Final result */
  int *m;                /* The cost matrix */
  char *cx;              /* Corresponding character values */
  int *toFree = 0;       /* Malloced space */
  int nMatch = 0;
  int mStack[60+15];     /* Stack space to use if not too much is needed */

  /* Early out if either input is NULL */
  if( zA==0 || zB==0 ) return -1;

  /* Skip any common prefix */
  while( zA[0] && zA[0]==zB[0] ){ dc = zA[0]; zA++; zB++; nMatch++; }
  if( pnMatch ) *pnMatch = nMatch;
  if( zA[0]==0 && zB[0]==0 ) return 0;

#if 0
  printf("A=\"%s\" B=\"%s\" dc=%c\n", zA, zB, dc?dc:' ');
#endif

  /* Verify input strings and measure their lengths */
  for(nA=0; zA[nA]; nA++){
    if( zA[nA]&0x80 ) return -2;
  }
  for(nB=0; zB[nB]; nB++){
    if( zB[nB]&0x80 ) return -2;
  }

  /* Special processing if either string is empty */
  if( nA==0 ){
    cBprev = (char)dc;
    for(xB=res=0; (cB = zB[xB])!=0; xB++){
      res += insertOrDeleteCost(cBprev, cB, zB[xB+1])/FINAL_INS_COST_DIV;
      cBprev = cB;
    }
    return res;
  }
  if( nB==0 ){
    cAprev = (char)dc;
    for(xA=res=0; (cA = zA[xA])!=0; xA++){
      res += insertOrDeleteCost(cAprev, cA, zA[xA+1]);
      cAprev = cA;
    }
    return res;
  }

  /* A is a prefix of B */
  if( zA[0]=='*' && zA[1]==0 ) return 0;

  /* Allocate and initialize the Wagner matrix */
  if( nB<(sizeof(mStack)*4)/(sizeof(mStack[0])*5) ){
    m = mStack;
  }else{
    m = toFree = sqlite3_malloc64( (nB+1)*5*sizeof(m[0])/4 );
    if( m==0 ) return -3;
  }
  cx = (char*)&m[nB+1];

  /* Compute the Wagner edit distance */
  m[0] = 0;
  cx[0] = (char)dc;
  cBprev = (char)dc;
  for(xB=1; xB<=nB; xB++){
    cBnext = zB[xB];
    cB = zB[xB-1];
    cx[xB] = cB;
    m[xB] = m[xB-1] + insertOrDeleteCost(cBprev, cB, cBnext);
    cBprev = cB;
  }
  cAprev = (char)dc;
  for(xA=1; xA<=nA; xA++){
    int lastA = (xA==nA);
    cA = zA[xA-1];
    cAnext = zA[xA];
    if( cA=='*' && lastA ) break;
    d = m[0];
    dc = cx[0];
    m[0] = d + insertOrDeleteCost(cAprev, cA, cAnext);
    cBprev = 0;
    for(xB=1; xB<=nB; xB++){
      int totalCost, insCost, delCost, subCost, ncx;
      cB = zB[xB-1];
      cBnext = zB[xB];

      /* Cost to insert cB */
      insCost = insertOrDeleteCost(cx[xB-1], cB, cBnext);
      if( lastA ) insCost /= FINAL_INS_COST_DIV;

      /* Cost to delete cA */
      delCost = insertOrDeleteCost(cx[xB], cA, cBnext);

      /* Cost to substitute cA->cB */
      subCost = substituteCost(cx[xB-1], cA, cB);

      /* Best cost */
      totalCost = insCost + m[xB-1];
      ncx = cB;
      if( (delCost + m[xB])<totalCost ){
        totalCost = delCost + m[xB];
        ncx = cA;
      }
      if( (subCost + d)<totalCost ){
        totalCost = subCost + d;
      }

#if 0
      printf("%d,%d d=%4d u=%4d r=%4d dc=%c cA=%c cB=%c"
             " ins=%4d del=%4d sub=%4d t=%4d ncx=%c\n",
             xA, xB, d, m[xB], m[xB-1], dc?dc:' ', cA, cB,
             insCost, delCost, subCost, totalCost, ncx?ncx:' ');
#endif

      /* Update the matrix */
      d = m[xB];
      dc = cx[xB];
      m[xB] = totalCost;
      cx[xB] = (char)ncx;
      cBprev = cB;
    }
    cAprev = cA;
  }

  /* Free the wagner matrix and return the result */
  if( cA=='*' ){
    res = m[1];
    for(xB=1; xB<=nB; xB++){
      if( m[xB]<res ){
        res = m[xB];
        if( pnMatch ) *pnMatch = xB+nMatch;
      }
    }
  }else{
    res = m[nB];
    /* In the current implementation, pnMatch is always NULL if zA does
    ** not end in "*" */
    assert( pnMatch==0 );
  }
  sqlite3_free(toFree);
  return res;
}