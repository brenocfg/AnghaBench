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
struct stat {int st_size; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  Cksum ;

/* Variables and functions */
 int /*<<< orphan*/  ISDIGIT (char) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  decode_btree_page (unsigned char*,int,int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  fstat (scalar_t__,struct stat*) ; 
 unsigned char* getContent (int,int) ; 
 int /*<<< orphan*/  lseek (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int mxFrame ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int pagesize ; 
 int /*<<< orphan*/  print_frame (int) ; 
 int /*<<< orphan*/  print_oneline_frame (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_wal_header (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  read (scalar_t__,unsigned char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate (char*,int) ; 

int main(int argc, char **argv){
  struct stat sbuf;
  unsigned char zPgSz[4];
  if( argc<2 ){
    fprintf(stderr,"Usage: %s FILENAME ?PAGE? ...\n", argv[0]);
    exit(1);
  }
  fd = open(argv[1], O_RDONLY);
  if( fd<0 ){
    fprintf(stderr,"%s: can't open %s\n", argv[0], argv[1]);
    exit(1);
  }
  zPgSz[0] = 0;
  zPgSz[1] = 0;
  lseek(fd, 8, SEEK_SET);
  read(fd, zPgSz, 4);
  pagesize = zPgSz[1]*65536 + zPgSz[2]*256 + zPgSz[3];
  if( pagesize==0 ) pagesize = 1024;
  printf("Pagesize: %d\n", pagesize);
  fstat(fd, &sbuf);
  if( sbuf.st_size<32 ){
    printf("file too small to be a WAL\n");
    return 0;
  }
  mxFrame = (sbuf.st_size - 32)/(pagesize + 24);
  printf("Available pages: 1..%d\n", mxFrame);
  if( argc==2 ){
    int i;
    Cksum x;
    print_wal_header(&x);
    for(i=1; i<=mxFrame; i++){
      print_oneline_frame(i, &x);
    }
  }else{
    int i;
    for(i=2; i<argc; i++){
      int iStart, iEnd;
      char *zLeft;
      if( strcmp(argv[i], "header")==0 ){
        print_wal_header(0);
        continue;
      }
      if( !ISDIGIT(argv[i][0]) ){
        fprintf(stderr, "%s: unknown option: [%s]\n", argv[0], argv[i]);
        continue;
      }
      iStart = strtol(argv[i], &zLeft, 0);
      if( zLeft && strcmp(zLeft,"..end")==0 ){
        iEnd = mxFrame;
      }else if( zLeft && zLeft[0]=='.' && zLeft[1]=='.' ){
        iEnd = strtol(&zLeft[2], 0, 0);
      }else if( zLeft && zLeft[0]=='b' ){
        int ofst, nByte, hdrSize;
        unsigned char *a;
        if( iStart==1 ){
          hdrSize = 100;
          ofst = hdrSize = 100;
          nByte = pagesize-100;
        }else{
          hdrSize = 0;
          ofst = (iStart-1)*pagesize;
          nByte = pagesize;
        }
        ofst = 32 + hdrSize + (iStart-1)*(pagesize+24) + 24;
        a = getContent(ofst, nByte);
        decode_btree_page(a, iStart, hdrSize, zLeft+1);
        free(a);
        continue;
#if !defined(_MSC_VER)
      }else if( zLeft && strcmp(zLeft,"truncate")==0 ){
        /* Frame number followed by "truncate" truncates the WAL file
        ** after that frame */
        off_t newSize = 32 + iStart*(pagesize+24);
        truncate(argv[1], newSize);
        continue;
#endif
      }else{
        iEnd = iStart;
      }
      if( iStart<1 || iEnd<iStart || iEnd>mxFrame ){
        fprintf(stderr,
          "Page argument should be LOWER?..UPPER?.  Range 1 to %d\n",
          mxFrame);
        exit(1);
      }
      while( iStart<=iEnd ){
        print_frame(iStart);
        iStart++;
      }
    }
  }
  close(fd);
  return 0;
}