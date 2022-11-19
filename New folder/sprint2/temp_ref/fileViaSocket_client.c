#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>


#define SIZE 1024


const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

void send_file(FILE *fp, int sockfd, const char *ext){
  int n;
  char data[SIZE] = {0};
 send(sockfd, ext, sizeof(ext), 0);
  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}

int main(int argc, char const *argv[]){
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;
 
  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
  
 if(argv[1]==NULL){
  printf("No file name arg passed.\n");
  exit(0);
 }
 const char *filename = argv[1];
 printf("%s\n",get_filename_ext(filename) );
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("Error in socket");
    exit(1);
  }
  printf("Server socket created successfully.\n");
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
 
  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("Error in socket");
    exit(1);
  }
 printf("Connected to Server.\n");
 
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("Error in reading file.");
    exit(1);
  }
  const char *ext = get_filename_ext(filename);
  send_file(fp, sockfd, ext);
  printf("File data sent successfully.\n");
 
  printf("Closing the connection.\n");
  close(sockfd);
 
  return 0;
}