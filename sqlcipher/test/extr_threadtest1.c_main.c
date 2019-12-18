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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sig ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char* sqlite3_mprintf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ thread_cnt ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int verbose ; 
 int /*<<< orphan*/  worker_bee ; 

int main(int argc, char **argv){
  char *zFile;
  int i, n;
  pthread_t id;
  if( argc>2 && strcmp(argv[1], "-v")==0 ){
    verbose = 1;
    argc--;
    argv++;
  }
  if( argc<2 || (n=atoi(argv[1]))<1 ) n = 10;
  for(i=0; i<n; i++){
    char zBuf[200];
    sprintf(zBuf, "testdb-%d", (i+1)/2);
    unlink(zBuf);
  }
  for(i=0; i<n; i++){
    zFile = sqlite3_mprintf("%d.testdb-%d", i%2+1, (i+2)/2);
    if( (i%2)==0 ){
      /* Remove both the database file and any old journal for the file
      ** being used by this thread and the next one. */
      char *zDb = &zFile[2];
      char *zJournal = sqlite3_mprintf("%s-journal", zDb);
      unlink(zDb);
      unlink(zJournal);
      free(zJournal);
    }
      
    pthread_create(&id, 0, worker_bee, (void*)zFile);
    pthread_detach(id);
  }
  pthread_mutex_lock(&lock);
  while( thread_cnt>0 ){
    pthread_cond_wait(&sig, &lock);
  }
  pthread_mutex_unlock(&lock);
  for(i=0; i<n; i++){
    char zBuf[200];
    sprintf(zBuf, "testdb-%d", (i+1)/2);
    unlink(zBuf);
  }
  return 0;
}