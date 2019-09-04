#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  outbuffer ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_11__ {int _bufsiz; } ;
typedef  int LONG ;
typedef  TYPE_1__ FILE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  IOMODE ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int _S_IREAD ; 
 int _S_IWRITE ; 
 int _getw (TYPE_1__*) ; 
 int close (int) ; 
 int /*<<< orphan*/  fclose (TYPE_1__*) ; 
 TYPE_1__* fdopen (int,char*) ; 
 scalar_t__ feof (TYPE_1__*) ; 
 scalar_t__ fgets (char*,unsigned int,TYPE_1__*) ; 
 int fread (char*,int,int,TYPE_1__*) ; 
 scalar_t__ fseek (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int ftell (TYPE_1__*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int open (char*,int,...) ; 
 int /*<<< orphan*/  rewind (TYPE_1__*) ; 
 unsigned int strlen (char const*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int write (int,char const*,int) ; 

__attribute__((used)) static void test_readmode( BOOL ascii_mode )
{
    static const char outbuffer[] = "0,1,2,3,4,5,6,7,8,9\r\n\r\nA,B,C,D,E\r\nX,Y,Z";
    static const char padbuffer[] = "ghjghjghjghj";
    static const char nlbuffer[] = "\r\n";
    static char buffer[8192];
    const char *optr;
    int fd;
    FILE *file;
    const int *ip;
    int i, j, m, ao, pl;
    unsigned int fp;
    LONG l;

    fd = open ("fdopen.tst", O_WRONLY | O_CREAT | O_BINARY, _S_IREAD |_S_IWRITE);
    /* an internal buffer of BUFSIZ is maintained, so make a file big
     * enough to test operations that cross the buffer boundary 
     */
    j = (2*BUFSIZ-4)/strlen(padbuffer);
    for (i=0; i<j; i++)
        write (fd, padbuffer, strlen(padbuffer));
    j = (2*BUFSIZ-4)%strlen(padbuffer);
    for (i=0; i<j; i++)
        write (fd, &padbuffer[i], 1);
    write (fd, nlbuffer, strlen(nlbuffer));
    write (fd, outbuffer, sizeof (outbuffer));
    close (fd);
    
    if (ascii_mode) {
        /* Open file in ascii mode */
        fd = open ("fdopen.tst", O_RDONLY);
        file = fdopen (fd, "r");
        ao = -1; /* on offset to account for carriage returns */
    }
    else {
        fd = open ("fdopen.tst", O_RDONLY | O_BINARY);
        file = fdopen (fd, "rb");
        ao = 0;
    }
    
    /* first is a test of fgets, ftell, fseek */
    ok(ftell(file) == 0,"Did not start at beginning of file in %s\n", IOMODE);
    ok(fgets(buffer,2*BUFSIZ+256,file) !=0,"padding line fgets failed unexpected in %s\n", IOMODE);
    l = ftell(file);
    pl = 2*BUFSIZ-2;
    ok(l == pl,"padding line ftell got %d should be %d in %s\n", l, pl, IOMODE);
    ok(lstrlenA(buffer) == pl+ao,"padding line fgets got size %d should be %d in %s\n",
     lstrlenA(buffer), pl+ao, IOMODE);
    for (fp=0; fp<strlen(outbuffer); fp++)
        if (outbuffer[fp] == '\n') break;
    fp++;
    ok(fgets(buffer,256,file) !=0,"line 1 fgets failed unexpected in %s\n", IOMODE);
    l = ftell(file);
    ok(l == pl+fp,"line 1 ftell got %d should be %d in %s\n", l, pl+fp, IOMODE);
    ok(lstrlenA(buffer) == fp+ao,"line 1 fgets got size %d should be %d in %s\n",
     lstrlenA(buffer), fp+ao, IOMODE);
    /* test a seek back across the buffer boundary */
    l = pl;
    ok(fseek(file,l,SEEK_SET)==0,"seek failure in %s\n", IOMODE);
    l = ftell(file);
    ok(l == pl,"ftell after seek got %d should be %d in %s\n", l, pl, IOMODE);
    ok(fgets(buffer,256,file) !=0,"second read of line 1 fgets failed unexpected in %s\n", IOMODE);
    l = ftell(file);
    ok(l == pl+fp,"second read of line 1 ftell got %d should be %d in %s\n", l, pl+fp, IOMODE);
    ok(lstrlenA(buffer) == fp+ao,"second read of line 1 fgets got size %d should be %d in %s\n",
     lstrlenA(buffer), fp+ao, IOMODE);
    ok(fgets(buffer,256,file) !=0,"line 2 fgets failed unexpected in %s\n", IOMODE);
    fp += 2;
    l = ftell(file);
    ok(l == pl+fp,"line 2 ftell got %d should be %d in %s\n", l, pl+fp, IOMODE);
    ok(lstrlenA(buffer) == 2+ao,"line 2 fgets got size %d should be %d in %s\n",
     lstrlenA(buffer), 2+ao, IOMODE);
    
    /* test fread across buffer boundary */
    rewind(file);
    ok(ftell(file) == 0,"Did not start at beginning of file in %s\n", IOMODE);
    ok(fgets(buffer,BUFSIZ-6,file) !=0,"padding line fgets failed unexpected in %s\n", IOMODE);
    j=strlen(outbuffer);
    i=fread(buffer,1,BUFSIZ+strlen(outbuffer),file);
    ok(i==BUFSIZ+j,"fread failed, expected %d got %d in %s\n", BUFSIZ+j, i, IOMODE);
    l = ftell(file);
    ok(l == pl+j-(ao*4)-5,"ftell after fread got %d should be %d in %s\n", l, pl+j-(ao*4)-5, IOMODE);
    for (m=0; m<3; m++)
        ok(buffer[m]==padbuffer[m+(BUFSIZ-4)%strlen(padbuffer)],"expected %c got %c\n", padbuffer[m], buffer[m]);
    m+=BUFSIZ+2+ao;
    optr = outbuffer;
    for (; m<i; m++) {
        ok(buffer[m]==*optr,"char %d expected %c got %c in %s\n", m, *optr, buffer[m], IOMODE);
        optr++;
        if (ao && (*optr == '\r'))
            optr++;
    }
    /* fread should return the requested number of bytes if available */
    rewind(file);
    ok(ftell(file) == 0,"Did not start at beginning of file in %s\n", IOMODE);
    ok(fgets(buffer,BUFSIZ-6,file) !=0,"padding line fgets failed unexpected in %s\n", IOMODE);
    j = fp+10;
    i=fread(buffer,1,j,file);
    ok(i==j,"fread failed, expected %d got %d in %s\n", j, i, IOMODE);
    /* test fread eof */
    ok(fseek(file,0,SEEK_END)==0,"seek failure in %s\n", IOMODE);
    ok(feof(file)==0,"feof failure in %s\n", IOMODE);
    ok(fread(buffer,1,1,file)==0,"fread failure in %s\n", IOMODE);
    ok(feof(file)!=0,"feof failure in %s\n", IOMODE);
    ok(fseek(file,-3,SEEK_CUR)==0,"seek failure in %s\n", IOMODE);
    ok(feof(file)==0,"feof failure in %s\n", IOMODE);
    ok(fread(buffer,2,1,file)==1,"fread failed in %s\n", IOMODE);
    ok(feof(file)==0,"feof failure in %s\n", IOMODE);
    ok(fread(buffer,2,1,file)==0,"fread failure in %s\n",IOMODE);
    ok(feof(file)!=0,"feof failure in %s\n", IOMODE);

    /* test some additional functions */
    rewind(file);
    ok(ftell(file) == 0,"Did not start at beginning of file in %s\n", IOMODE);
    ok(fgets(buffer,2*BUFSIZ+256,file) !=0,"padding line fgets failed unexpected in %s\n", IOMODE);
    i = _getw(file);
    ip = (const int *)outbuffer;
    ok(i == *ip,"_getw failed, expected %08x got %08x in %s\n", *ip, i, IOMODE);
    for (fp=0; fp<strlen(outbuffer); fp++)
        if (outbuffer[fp] == '\n') break;
    fp++;
    /* this will cause the next _getw to cross carriage return characters */
    ok(fgets(buffer,fp-6,file) !=0,"line 1 fgets failed unexpected in %s\n", IOMODE);
    for (i=0, j=0; i<6; i++) {
        if (ao==0 || outbuffer[fp-3+i] != '\r')
            buffer[j++] = outbuffer[fp-3+i];
    }
    i = _getw(file);
    ip = (int *)buffer;
    ok(i == *ip,"_getw failed, expected %08x got %08x in %s\n", *ip, i, IOMODE);

    fclose (file);
    unlink ("fdopen.tst");

    /* test INTERNAL_BUFSIZ read containing 0x1a character (^Z) */
    fd = open("fdopen.tst", O_WRONLY | O_CREAT | O_BINARY, _S_IREAD |_S_IWRITE);
    ok(fd != -1, "open failed\n");
    memset(buffer, 'a', sizeof(buffer));
    buffer[1] = 0x1a;
    ok(write(fd, buffer, sizeof(buffer)) == sizeof(buffer), "write failed\n");
    ok(close(fd) != -1, "close failed\n");

    fd = open("fdopen.tst", O_RDONLY);
    ok(fd != -1, "open failed\n");
    file = fdopen(fd, ascii_mode ? "r" : "rb");
    ok(file != NULL, "fdopen failed\n");

    memset(buffer, 0, sizeof(buffer));
    i = fread(buffer, 4096, 1, file);
    ok(!i, "fread succeeded\n");
    ok(file->_bufsiz == 4096, "file->_bufsiz = %d\n", file->_bufsiz);
    for(i=0; i<4096; i++)
        if(buffer[i] != (i==1 ? 0x1a : 'a')) break;
    ok(i==4096, "buffer[%d] = %d\n", i, buffer[i]);

    fclose(file);
    unlink("fdopen.tst");
}