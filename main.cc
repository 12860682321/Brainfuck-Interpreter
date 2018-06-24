/*
    This is a Brain fuck interpreter

*/

#include <iostream>
#include <string>
#include <stdexcept>

char strip[20];
std::string command;
unsigned int instructPtr;
char* dataptr=strip;
int bracketCounter;

void showStrip() {
    for(int i = 0; i < 20; ++i){
        std::cout<<(int)strip[i]<<" ";
    }
    std::cout<<"\n";
    for(unsigned int i = 0; i < (dataptr - strip); ++i){
        std::cout<<"  ";
    }
    std::cout<<"^\n";
    std::cout<<command<<"\n";
}

unsigned int gotoCorrespondingClosingBracket(){
    while(++instructPtr < command.size()){
        if(command[instructPtr] == '[') ++bracketCounter;
        if(command[instructPtr] == ']') --bracketCounter;
        if(!bracketCounter) return bracketCounter;
    }
    throw std::runtime_error("Brackets not balanced!");
}

unsigned int gotoCorrespondingOpeningBracket(){
    while(--instructPtr >= 0){
        if(command[instructPtr] == '[') ++bracketCounter;
        if(command[instructPtr] == ']') --bracketCounter;
        if(!bracketCounter) return bracketCounter;
    }
    throw std::runtime_error("Brackets not balanced!");
}

void interpretCommand(char c){
    switch(c){
        case '>':
            ++dataptr;
            break;
        case '<':
            --dataptr;
            break;
        case '+':
            ++*dataptr;
            break;
        case '-':
            --*dataptr;
            break;
        case '.':
            std::putchar(*dataptr);
            break;
        case ',':
            std::cout<<"Input a byte for data cell "<<*dataptr<<" :";
            char temp; std::cin>>temp;
            *dataptr = temp;
            std::cout<<"\n";
            break;
        case '[':
            ++bracketCounter;
            if(!*dataptr){
                instructPtr = gotoCorrespondingClosingBracket();
                break;
            }
            break;
        case ']':
            --bracketCounter;
            if(*dataptr) {
                instructPtr = gotoCorrespondingOpeningBracket();
                break;
            }
            break;
        case ' ':
        case '\n':
            break;
        default:
            std::cout<<"Not a valid command\n";

    }
}

int main(){
    std::cout<<"BrainFuck interpreter\n\n";
    showStrip();
    while(std::cin>>command){
        for(instructPtr = 0; instructPtr < command.size(); ++instructPtr){
            interpretCommand(command[instructPtr]);
        }
        showStrip();
    }
    return 0;
}