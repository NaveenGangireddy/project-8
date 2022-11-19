#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>

#define SIZE 1024


void write_file(int sockfd){
  int n;
  FILE *fp;
  char filename[] = "received_";
  char buffer[SIZE];
  
  n = recv(sockfd, buffer, SIZE, 0);
  strcat(filename, buffer);
  printf("%s\n", filename);
  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  return;
}