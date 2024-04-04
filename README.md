# Description 
Format the plots created by ROOT CERN
# Usage
1. Copy `Lansxlogon.h` file to the $ROOT/include path.
2. Include this head file in your marco and  call the myStyle() function. For instance:
   ```C++
   #include "Lansxlogon.h"
   void Plot()
   {
     myStyle();
   }
   ```