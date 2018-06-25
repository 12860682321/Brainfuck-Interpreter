/*
    This is a Brainfuck interpreter
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>

char tape[100];
std::string command;
unsigned int PC;         // This is the program counter
char* dataPtr = tape;

void interpretCommand(char c);
void showTape();
void gotoCorrespondingBracket(bool findClosingBracket);

int main(){
    std::cout<<"BrainFuck interpreter\n\n";
    showTape();
    std::cout<<"\n";
    while(std::getline(std::cin,command)){
        for(PC = 0; PC < command.size(); ++PC){
            interpretCommand(command[PC]);
        }
        showTape();
        std::cout<<std::setbase(16)<<"data ptr"<<dataPtr<<"\n";
    }
    return 0;
}

void interpretCommand(char c){
    switch(c){
        case '>': case '<':
            (c == '>')? ++dataPtr : --dataPtr;
            break;
        case '+': case '-':
            (c == '+')? ++*dataPtr : --*dataPtr;
            break;
        case '.':
            std::cout<<"Byte at cell "<<(dataPtr - tape)<<" is: "<<*dataPtr<<"\n";
            break;
        case ',':
            *dataPtr = command[++PC];
            break;
        case '[':
            if(!*dataPtr) gotoCorrespondingBracket(true);
            break;
        case ']':
            if(*dataPtr) gotoCorrespondingBracket(false);       
            break;
        default:
            if(c != ' ') std::cout<<"Not a valid command\n";
    }
}

void showTape() {
    std::cout<<"Tape: ";
    for(int i = 0; i < 100; ++i){
        std::cout<<(int)tape[i]<<" ";
    }
    std::cout<<"\nData Pointer is at cell: "<<(dataPtr - tape)<<"\n";
    std::cout<<"Commands: "<<command<<"\n";
}

void gotoCorrespondingBracket(bool findClosingBracket){
    int bracketCounter = (findClosingBracket)? 1 : -1;
    while((findClosingBracket)? ++PC : --PC < command.size()){
        if(command[PC] == '[' || command[PC] == ']') (command[PC] == '[')? ++bracketCounter : --bracketCounter;
        if(!bracketCounter) return;
    }
    throw std::runtime_error("Brackets not balanced!");
}