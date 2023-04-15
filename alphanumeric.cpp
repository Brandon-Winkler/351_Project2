#include <pthread.h>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstring>

std::vector<std::string> tokens;


void * alphaThread(void * arg) {
    char* alphaType = "alpha";
    std::string* inputString = (std::string*) arg;

    for(int j = 0; j < inputString->size(); ++j) {

        if(isdigit((*inputString)[j])) break;
        pthread_exit((void*)alphaType);
    }   
    pthread_exit(NULL); 
}

void * numericThread(void * arg) {

    bool hasNum = false;
    char* numericType = "numeric";
    std::string* inputString = (std::string*) arg;

    for(int j = 0; j < inputString->size(); ++j) {

        if(isdigit((*inputString)[j])) hasNum = true;    
    }
    
    if(hasNum == true)  pthread_exit((void*)numericType);
    hasNum == false;

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    std::string readIn = argv[1];
    std::string token = "";
    char* tokenType;

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

        if(pthread_join(tid1, (void**)tokenType) != NULL){
            std::cout << tokenType << ": " << token;
        }
        if(pthread_join(tid2, (void**)tokenType) != NULL){
            std::cout << tokenType << ": " << token;
        }
    }
    return 0;
}