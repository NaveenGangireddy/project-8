#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024


using namespace std;


void init_server(){
    char *ip = "127.0.0.1";
  int port = 8080;
  int bound;
 
  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];
 
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("Error in socket");
    exit(1);
  }
  printf("Server socket created successfully.\n");
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
 
  bound = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(bound < 0) {
    perror("Error in bind");
    exit(1);
  }
  printf("Binding successfull.\n");
 
  if(listen(sockfd, 10) == 0){
 printf("Listening....\n");
 }else{
 perror("Error in listening");
    exit(1);
 }
 
  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
//   write_file(new_sock);
  printf("Data written in the file successfully.\n");
}