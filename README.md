# Description 
Format the plots created by ROOT CERN and Provide some functions to set the Line/Marker/ attributions （one line of code）

---

**ROOT Version**: >6
**Platform**: Win10/11,Ubuntu,WSL

---


# Usage
1. Copy `Lansxlogon.h` file to the $ROOTSYS/include path.
2. Include this head file in your marco and  call the myStyle() function. For instance:
   ```C++
   #include "Lansxlogon.h"
   void Plot()
   {
     myStyle();
   }
   ```
