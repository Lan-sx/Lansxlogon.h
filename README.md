# Description 
Format the plots created by ROOT CERN and Provide some functions to set the Line/Marker/ attributions （one line of code）

---

**ROOT Version**: >6
**Platform**: Win10/11,Ubuntu,WSL

---


# Usage
1. Copy `Lansxlogon.h` file to the $ROOTSYS/include path.
2. Include this head file in your marco and  call the `LansxFormat::myStyle()` function. For instance:
3. When Drawing several `TGraph`/`TF1`/`TH`, it may need to repeat some similar code (like `SetXXX(kXXX)`) to set the Line/Marker/Fill attributions of each Object. 
You can call `LansxFormat::FormatAll(obj,"%a %b ... %g%h",kRed,kDashed,3,...,3003)` to set these attributions in one line. 
   ```C++
   #include "Lansxlogon.h"
   void Plot()
   {
       LansxFormat::myStyle();

       // LansxFormat::FormatAll(obj,"",...) is a function that can accept a variable number of arguments, like std::printf()
       // "%a%b%c%d%e%f%g%h" a,b,c ->  SetLineColor/SetLineStyle/SetLineWidth
       //                    d,e,f ->  SetMarkerColor/SetMarkerStyle/SetMarkerSize
       //                    g,h   ->  SetFillColor/SetFillStyle
       //  

       //----------------------------------------------------------------
       //Examples
       //Set line color/style, marker color/style for a TGraph
       LansxFormat::FormatAll(gr,"%a%b%d%e",kRed,kDashed,kRed,kFullSquare); // -> SetLineColor(kRed);SetLineStyle(kDashed);SetMarkerColor(kRed);SetMarkerStyle(kFullSquare);
       //Set line color, fill color/style for a TH1
       LansxFormat::FormatAll(h1,"%a %h %g",kBlue,3003,kBlue);              // -> SetLineColor(kBlue);SetFillStyle(3003);SetFillColor(kBlue);
   }
   ```
