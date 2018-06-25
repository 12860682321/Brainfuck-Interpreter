/*
    This is a Brainfuck interpreter
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

char tape[100];
std::string command = ""; 
unsigned int PC;           // This is the program counter
char* dataPtr = tape;

void interpretCommand(char c);
void showTape();
void gotoCorrespondingBracket(bool findClosingBracket);

int main(int argc, char* argv[]){
    bool fromFile = false;
    std::fstream infile;
    if(argc > 2) { 
        std::cout<<"Usage: ./Brainfuck-Interpreter file\n"; 
        return 0; 
    }
    if(argc == 2) fromFile = true; 
    if(fromFile) infile.open(argv[1],std::ios_base::in);
    std::cout<<"BrainFuck interpreter\n\n";
    showTape();
    std::cout<<"\n";
    std::string input;
    int bracketCounter = 0;
    if(!fromFile) std::cout<<"Command:";
    while((fromFile)? std::getline(infile, input) : std::getline(std::cin, input)){
        input = input.substr(0,input.find("//"));
        for(unsigned int i = 0; i < input.size(); ++i){
            if(input[i] == '[' || input[i] == ']') (input[i] == '[')? ++bracketCounter : --bracketCounter;
            command += input[i];
            if(input[i] == ',') (fromFile)? command += std::cin.get() : command += input[++i] ;
        }
        if(!bracketCounter){
            for(PC = 0; PC < command.size(); ++PC){
                interpretCommand(command[PC]);
            }
            command = "";
            if(!fromFile) showTape();
            if(!fromFile) std::cout<<"Command: ";
        } 
    }
    if(fromFile) infile.close();
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
}

void gotoCorrespondingBracket(bool findClosingBracket){
    int bracketCounter = (findClosingBracket)? 1 : -1;
    while((findClosingBracket)? ++PC : --PC < command.size()){
        if(command[PC] == '[' || command[PC] == ']') (command[PC] == '[')? ++bracketCounter : --bracketCounter;
        if(!bracketCounter) return;
    }
    throw std::runtime_error("Brackets not balanced!");
}