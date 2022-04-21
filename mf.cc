
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
void mf(int ny, int nx, int hy, int hx, const float *in, float *out) {
  std::vector<double> window((2*hx+1) * (2*hy+1), 1000.0);
  int n,bi,bj, ei,ej;

  for(int i = 0; i < nx; i++){
    for(int j = 0; j < ny; j++){ 

      //left upper coordinate of window (bi,bj)
      if(i-hx >= 0){ //middle section
        bi = i-hx;
      }else{
        bi = 0 ;
      }
      if(j-hy >= 0){ //middle section
        bj = j-hy;
      }else{
        bj = 0 ;
      }

      //right bottom coordinate of window (ei,ej)
      if(i+hx < nx){ //middle section
        ei = i+hx;
      }else{
        ei = nx-1 ;
      }
      if(j+hy < ny){ //middle section
        ej = j+hy;
      }else{
        ej = ny-1 ;
      }

      n= 0;

      for(int wi = bi; wi <= ei;wi ++){
        for(int wj = bj; wj <= ej;wj ++){
          window[n] = in[wi + nx*wj];
          n = n+ 1;
        }
      }

      int k = 0;

      while(n+k < int( window.size())){
        window[n+k] = 1000; 
        k = k + 1;
       
      }

      auto m = window.begin() + n/2;
      std::nth_element(window.begin(), m, window.begin()+n);
      double med = window[n/2];

      
      if (n % 2== 0){ //If the set size is even
        auto max_it = max_element(window.begin(), window.begin()+n/2);
        med = (*max_it + med) / 2.0;
        
      }
      
      out[i + nx*j] = med; 
     
      
      

    }
  }
  

}
