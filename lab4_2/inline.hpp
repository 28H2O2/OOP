#ifndef _INLINE_H_
#define _INLINE_H_

#include<cstring>

inline const int position(char c){
    const int int_c = (int)c;
    return (int_c * 8) - 256;
}


#endif

