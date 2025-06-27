#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>

int main(){
    // main socket that listens for clients
    int server_fd; 
     // socket for talking with one client
    int client_fd;
    //stores IP address , port number, Address Type
    struct sockaddr_in server_addr; 

    char response[]= 
    "HTTP/1.1 200 OK\r\n" // tells browser that everthing is fine
    "Content-Type: text/html\r\n\r\n" // tells browser i am sending html content
    "<h1>Hello, world!</h1>"; // this shows on screen

    // create a socket
    // socket() : cretes a socket 
    // AF_INET : address family for IPv4
    // SOCK_STREAM : type of socket for TCP
    // 0 : default protocol (TCP)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(server_fd == 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // set address famly to ipv4
    server_addr.sin_family = AF_INET;

    server_addr.sin_addr.s_addr= INADDR_ANY;

    server_addr.sin_port = htons(8080); // port 8080


    if(bind(server_fd,(struct sockaddr *)&server_addr, sizeof(server_addr))<0){
        perror("Bind failed");
        exit(EXIT_FAILURE);

        listen(server_fd,10);

        printf('listening on port 8080...\n');

        while(1){
            client_fd = accept(server_fd,NULL,NULL);
            if(client_fd<0){
                perror("Accept failed");
                continue;
            }
            write(client_fd,response,sizeof(response)-1);
            close(client_fd);
            return 0;
        }

        
    }
}