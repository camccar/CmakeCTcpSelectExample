/*
struct InputParser {
  char* topic;
  int port1;
  int port2;

};

struct InputParser* New_InputParser(int argc, char *argv[]);

 */
#include "InputParser.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "ServerModel.h"

//void (*scan_file)(File *fp)

static struct ServerObject* getObject(FILE* fp){
  struct ServerObject* retVal = malloc(sizeof(struct ServerObject));
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  for(int i = 0; i < 3; ++i) {
    read = getline(&line,&len,fp);
    if(i == 0){
      retVal->topic = malloc(sizeof(char) * (len));
      for(int j = 0; j < strlen(line)-1; ++j){//Do not copy new line character
	retVal->topic[j] = line[j];
      }
    }
    if(i == 1){

      retVal->host = malloc(sizeof(char) * (len));
      for(int j = 0; j < strlen(line)-1; ++j){//Do not copy new line character
	retVal->host[j] = line[j];
      }
    }
    if(i == 2 ){
      retVal->port = atoi(line);
    }

  }

   if(line)
    free(line);
   
  return retVal;

}


static void scan_file(){
  //printf("Calling scan file!\n");
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen("config.txt","r");
  if(fp == NULL){
    printf("File probably not found\n");
    exit(EXIT_FAILURE);
  }

  while((read = getline(&line,&len,fp)) != -1) {
    //printf("Retrieved line of length %zu:\n",read);

    if(line[0] == '#'){
      // ignore comment lines
      continue;
    }
    if(strcmp(line,"server\n")==0){
      struct ServerObject* object = getObject(fp);
      printf("topic:%s\n",object->topic);
      printf("server:%s\n",object->host);
      printf("port:%d\n",object->port);
    }
    printf("%s" ,line);
    
    
  }

  fclose(fp);

   if(line)
    free(line);

  return;

}



static int CheckNextArgs(struct InputParser* P,int position, int argc, char *argv[]){
  if(argc-1 > position){
    printf(" grator than position\n");
    if( strcmp(argv[1+position],"-topic")){
      printf("return 0\n");
	return 0;
      }
  }
  printf("returning -1\n");
    return -1;
  

}



struct InputParser* New_InputParser(int argc, char *argv[]) {

  struct InputParser* retVal = malloc(sizeof(struct InputParser));

  int length = 0;
  for(int i = 1; i <argc; ++i){
    length = strlen(argv[i]);
    printf("\nLength:%d\n",length);
    puts(argv[i]);
    if(strcmp(argv[i],"topic")){
	printf("%d",CheckNextArgs(retVal,i,argc,argv));
    }
  }
  retVal->scan_file = scan_file;
  
  return retVal;

}


