#include <iostream>
#include <inttypes.h>

using namespace std;

int main(){
    uint16_t wordPtr;
    //uint16_t *words[2] = {HighWord, LowWord};
    uint16_t  words[2] = {0x34, 0xA6};

    for (int j=0; j<2; j++){
        wordPtr = words[j];

        if (wordPtr){
            //At least 1 fault
            for (int i=0; i<16; i++){
                if (wordPtr & (0x1 << i)){
                    printf("Raised fault #%i\n", i+(j*16));
                }
            }
        }
    }
}
