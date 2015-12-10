#include "function.h"

int serie(int n){
  if(n == 1){
    return 1;
  }
  if(n%2 == 0){
    return n + serie(n/2);
  }
  else if(n%2 == 1){
    return n + serie(3*n+1);
  }
}

int function(int rank, int rand){
  return serie(rank + rand);
}

