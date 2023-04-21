#include <pthread.h>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstring>

std::vector<std::string> tokens;
int i = 0;

void * alphaThread(void * arg) {

    while(i < tokens.size()){

        if(!isdigit(tokens[i][0])) {
            std::cout << "alpha: " << tokens[i] << '\n';
            ++i;
        }
    }
       
    pthread_exit(NULL); 
}

void * numericThread(void * arg) {

    while(i < tokens.size()){

        if(isdigit(tokens[i][0])){
            std::cout << "numeric: " << tokens[i] << '\n';
            ++i;
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    std::string readIn = argv[1];
    std::string token = "";

    for(int i = 0; i < readIn.size(); ++i) {

        token += readIn[i];

        if(readIn[i] == ' ') {

            tokens.push_back(token);
            token.clear();
        }
    }
    tokens.push_back(token);
    
    for(int i = 0; i < tokens.size(); ++i){

        pthread_t tid1, tid2;

        pthread_create(&tid1, NULL, &alphaThread  , (void*)& token);
        pthread_create(&tid2, NULL, &numericThread, (void*)& token);
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
    }
    return 0;
}