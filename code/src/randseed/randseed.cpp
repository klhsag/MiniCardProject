
#include <cassert>
#include <cstdlib>
#include <ctime>


namespace{
struct DefaultRandSeed{
    DefaultRandSeed(){
        srand(time(0));
    }
};
}


int next_rand(int module){
    static DefaultRandSeed seedSetter;
	assert(module > 0);
    return rand()%module;
}
