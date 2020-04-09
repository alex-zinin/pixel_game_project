#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<iostream>

#define PORT 2051

char* to_mass_char(std::string str){
    char* result = (char*) malloc(sizeof(char)*1024);

    for(int i = 0; i < str.size(); i++){
        result[i] = str[i];
    }

    return result;
}



void Str_And_mass(const std::string& str, char* buf){
    for(int i = 0; i < str.size(); i++){
        buf[i] = str[i];
    }
}

class Client{
public:
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char sbuff[1024] = {0};
    Client(){
        if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            // return -1;

        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);




        if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)  // строка -> в структуру сетевого адреса
        {
            printf("Not correct address");
            //return -1;

        }

        if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("Connection failed\n");
            // return -1;
        }

    }



    char* Get_Message(){
        memset(buffer, 0, 1024);
        valread = read(sock, buffer, 1024);


        fflush(stdout);
        return buffer;

    }

    void Send_Message(std::string str){
        Str_And_mass(str, sbuff);
        send(sock, sbuff, strlen(sbuff), 0);
        memset(sbuff, 0, 1024);
    }
};
