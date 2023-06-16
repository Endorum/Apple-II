#include <iostream>
#include <memory>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <bitset>


#define Byte uint8_t
#define Word uint16_t

using namespace std;

enum AddressMode{
    Accumulator,
    absolute,
    absolute_X,
    absolute_Y,
    immediate,
    implied,
    indirect,
    X_indexed,
    indexed_Y,
    relative,
    zeropage,
    zeropage_X,
    zeropage_Y,
    NONE
};



void printByte(Byte b){
    if(b<16){
        std::cout << '0' << hex << (int) b << dec;
    }else{
        std::cout << hex << (int)b << dec;
    }
}


void printWord(Word b){
    if(b<16){
        std::cout << "000" << hex << (int) b << dec;
    }
    else if(b>16 && b<256){
        std::cout << "00" << hex << (int) b << dec;
    }
    else if(b>256 && b<4096){
        std::cout << "0" << hex << (int) b << dec;
    }
    else if(b>4096){
        std::cout  << hex << (int) b << dec;
    }else{
        std::cout << "can't represent" << (int)b << " as Word!" << std::endl; 
        exit(1);
    }
}


class MOS_6502{
public:

    std::unique_ptr<Byte[]> memory{ new Byte[0x10000] };
    
    Byte A;
    Byte X;
    Byte Y;

    Byte Status;

    Word PC;
    Word SP;

    AddressMode mode[256] = {
        implied, indirect, NONE, NONE, NONE, zeropage, zeropage, NONE, implied, immediate, Accumulator, NONE, NONE, absolute, absolute, NONE,
        relative, indexed_Y, NONE, NONE, NONE, zeropage_X, zeropage_X, NONE, implied, absolute_Y, NONE, NONE, NONE, absolute_X, absolute_X, NONE,  
        absolute, indirect, NONE, NONE, zeropage, zeropage, zeropage, NONE, implied, immediate, Accumulator, NONE, absolute, absolute, absolute, NONE,
        relative, indexed_Y, NONE, NONE, NONE, zeropage_X, zeropage_X, NONE, implied, absolute_Y, NONE, NONE, NONE, absolute_X, absolute_X, NONE,  
        implied, indirect, NONE, NONE, NONE, zeropage, zeropage, NONE, implied, immediate, Accumulator, NONE, NONE, absolute, absolute, NONE,
        relative, indexed_Y, NONE, NONE, NONE, zeropage_X, zeropage_X, NONE, implied, absolute_Y, NONE, NONE, NONE, absolute_X, absolute_X, NONE,  
        relative, indexed_Y, NONE, NONE, NONE, zeropage_X, zeropage_X, NONE, implied, absolute_Y, NONE, NONE, NONE, absolute_X, absolute_X, NONE,  


    }

    Byte readByte(Word idx){
        return memory[idx];
    }
    
    void writeByte(Word idx, Byte data){
        memory[idx] = data;
    }

    void pushByte(Byte data){
        SP--;
        memory[SP] = data;

    }

    Byte popByte(){
        Byte res = memory[SP];
        SP++;
        return res;
    }

    void randomize(){
        for(int i=0;i<0x10000;i++){
            memory[i] = 0 + rand() % 256; 
        }
    }

    void reset(){
        A = 0;
        X = 0;
        Y = 0;
        Status = 0;
        PC = 0xFF00;
        SP = 0x01FF;
    }

    void showMemory(Word Start, Word End){
        std::cout << "Memory:\n";

        for(int i=Start; i<End+1; i++){
            Byte current = ( memory[i] );

            if (i % 16 == 0){
                std::cout << '\n';
            }

            
            if (i % 16 == 0){
                printWord(i);
                cout << " : " ;
            }

            printByte(current);
            cout << ' ' ;


        } 


    }

    void run(){


    }

    Word combine(Byte HB, Byte LB){
        Word res = LB;
        res = res | (HB<<8);

        return res;
    }


};


int main(){

    

    MOS_6502 cpu;
    cpu.reset();

    cpu.run();
    //cpu.randomize();
    cpu.memory[0xFFFF] = 0xff;
    cpu.showMemory(0xF100, 0xFFFF);
    

    return 0;
}