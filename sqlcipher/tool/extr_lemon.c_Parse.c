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
struct pstate {char* tokenstart; int tokenlineno; scalar_t__ errorcnt; int /*<<< orphan*/  firstrule; int /*<<< orphan*/  filename; int /*<<< orphan*/  state; struct lemon* gp; } ;
struct lemon {scalar_t__ errorcnt; int /*<<< orphan*/  rule; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  ps ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ErrorMsg (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  INITIALIZE ; 
 scalar_t__ ISALNUM (int) ; 
 scalar_t__ ISALPHA (char) ; 
 scalar_t__ ISSPACE (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 unsigned int fread (char*,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned int ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (unsigned int) ; 
 int /*<<< orphan*/  memset (struct pstate*,char,int) ; 
 int /*<<< orphan*/  parseonetoken (struct pstate*) ; 
 int /*<<< orphan*/  preprocess_input (char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

void Parse(struct lemon *gp)
{
  struct pstate ps;
  FILE *fp;
  char *filebuf;
  unsigned int filesize;
  int lineno;
  int c;
  char *cp, *nextcp;
  int startline = 0;

  memset(&ps, '\0', sizeof(ps));
  ps.gp = gp;
  ps.filename = gp->filename;
  ps.errorcnt = 0;
  ps.state = INITIALIZE;

  /* Begin by reading the input file */
  fp = fopen(ps.filename,"rb");
  if( fp==0 ){
    ErrorMsg(ps.filename,0,"Can't open this file for reading.");
    gp->errorcnt++;
    return;
  }
  fseek(fp,0,2);
  filesize = ftell(fp);
  rewind(fp);
  filebuf = (char *)malloc( filesize+1 );
  if( filesize>100000000 || filebuf==0 ){
    ErrorMsg(ps.filename,0,"Input file too large.");
    free(filebuf);
    gp->errorcnt++;
    fclose(fp);
    return;
  }
  if( fread(filebuf,1,filesize,fp)!=filesize ){
    ErrorMsg(ps.filename,0,"Can't read in all %d bytes of this file.",
      filesize);
    free(filebuf);
    gp->errorcnt++;
    fclose(fp);
    return;
  }
  fclose(fp);
  filebuf[filesize] = 0;

  /* Make an initial pass through the file to handle %ifdef and %ifndef */
  preprocess_input(filebuf);

  /* Now scan the text of the input file */
  lineno = 1;
  for(cp=filebuf; (c= *cp)!=0; ){
    if( c=='\n' ) lineno++;              /* Keep track of the line number */
    if( ISSPACE(c) ){ cp++; continue; }  /* Skip all white space */
    if( c=='/' && cp[1]=='/' ){          /* Skip C++ style comments */
      cp+=2;
      while( (c= *cp)!=0 && c!='\n' ) cp++;
      continue;
    }
    if( c=='/' && cp[1]=='*' ){          /* Skip C style comments */
      cp+=2;
      while( (c= *cp)!=0 && (c!='/' || cp[-1]!='*') ){
        if( c=='\n' ) lineno++;
        cp++;
      }
      if( c ) cp++;
      continue;
    }
    ps.tokenstart = cp;                /* Mark the beginning of the token */
    ps.tokenlineno = lineno;           /* Linenumber on which token begins */
    if( c=='\"' ){                     /* String literals */
      cp++;
      while( (c= *cp)!=0 && c!='\"' ){
        if( c=='\n' ) lineno++;
        cp++;
      }
      if( c==0 ){
        ErrorMsg(ps.filename,startline,
"String starting on this line is not terminated before the end of the file.");
        ps.errorcnt++;
        nextcp = cp;
      }else{
        nextcp = cp+1;
      }
    }else if( c=='{' ){               /* A block of C code */
      int level;
      cp++;
      for(level=1; (c= *cp)!=0 && (level>1 || c!='}'); cp++){
        if( c=='\n' ) lineno++;
        else if( c=='{' ) level++;
        else if( c=='}' ) level--;
        else if( c=='/' && cp[1]=='*' ){  /* Skip comments */
          int prevc;
          cp = &cp[2];
          prevc = 0;
          while( (c= *cp)!=0 && (c!='/' || prevc!='*') ){
            if( c=='\n' ) lineno++;
            prevc = c;
            cp++;
          }
        }else if( c=='/' && cp[1]=='/' ){  /* Skip C++ style comments too */
          cp = &cp[2];
          while( (c= *cp)!=0 && c!='\n' ) cp++;
          if( c ) lineno++;
        }else if( c=='\'' || c=='\"' ){    /* String a character literals */
          int startchar, prevc;
          startchar = c;
          prevc = 0;
          for(cp++; (c= *cp)!=0 && (c!=startchar || prevc=='\\'); cp++){
            if( c=='\n' ) lineno++;
            if( prevc=='\\' ) prevc = 0;
            else              prevc = c;
          }
        }
      }
      if( c==0 ){
        ErrorMsg(ps.filename,ps.tokenlineno,
"C code starting on this line is not terminated before the end of the file.");
        ps.errorcnt++;
        nextcp = cp;
      }else{
        nextcp = cp+1;
      }
    }else if( ISALNUM(c) ){          /* Identifiers */
      while( (c= *cp)!=0 && (ISALNUM(c) || c=='_') ) cp++;
      nextcp = cp;
    }else if( c==':' && cp[1]==':' && cp[2]=='=' ){ /* The operator "::=" */
      cp += 3;
      nextcp = cp;
    }else if( (c=='/' || c=='|') && ISALPHA(cp[1]) ){
      cp += 2;
      while( (c = *cp)!=0 && (ISALNUM(c) || c=='_') ) cp++;
      nextcp = cp;
    }else{                          /* All other (one character) operators */
      cp++;
      nextcp = cp;
    }
    c = *cp;
    *cp = 0;                        /* Null terminate the token */
    parseonetoken(&ps);             /* Parse the token */
    *cp = (char)c;                  /* Restore the buffer */
    cp = nextcp;
  }
  free(filebuf);                    /* Release the buffer after parsing */
  gp->rule = ps.firstrule;
  gp->errorcnt = ps.errorcnt;
}