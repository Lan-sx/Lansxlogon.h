/*********************************************************************
 * Author           : Lan-sx
 * Email            : shexin@ihep.ac.cn
 * Last modified    : 2024-03-04 18:33
 * Filename         : Lansxlogon.h
 * Description      : Plot Sty ref Doc. X.Z Liang IHEP,CAS
 *                    2023.12.11 : Add some FormatXXX Functions
 *                    2024.03.03 : Add a function to insert logo
 *                    2024.03.09 : Add a function to move multi StatBoxes
 *                                 (Only for TH1)
 * ******************************************************************/

//I need thick line for the frame and hist/functions
//Large white space surrounding the plot
//black font is used as the default font

#include <iostream>
#include <vector>
#include <cstdarg>
#include <cstdio>
#include "TObject.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TColor.h"
#include "TAttLine.h"
#include "TAttMarker.h"
#include "TAttFill.h"
#include "TImage.h"
#include "TString.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH1.h"
#include "TPaveStats.h"

namespace LansxFormat{

//Format linecolor linesty linewidth 
void FormatLine(TAttLine* attl,int col=2,int sty=1,int w=2)
{
    attl->SetLineColor(col);
    attl->SetLineStyle(sty);
    attl->SetLineWidth(w);
}

//FormatMarker markercolor markerstyle markersize 
void FormatMarker(TAttMarker* attm,int col=2,int sty=20,int size=1,double alpha=1.)
{
    attm->SetMarkerColorAlpha(col,alpha);
    attm->SetMarkerStyle(sty);
    attm->SetMarkerSize(size);
}

//FormatFill fillcolor fillstyle =3001-3025 1001 and 0
//pattern_number= ijk FillStyle = 3ijk
//                i (1-9) specify the space between each hatch 
//                j (0-9) specify angle between 0 and 90 degrees
//                k (0-9) specify angle between 90 and 180 degrees
void FormatFill(TAttFill* attfill,int col=2,int sty=3005)
{
    attfill->SetFillColor(col);
    //attfill->SetFillColorAlpha(col,0.2);
    attfill->SetFillStyle(sty);
}

//FormatAll
void FormatAll(TObject* obj,const char*fmt,...)
{
    //fmt 
    // "%a%b%c%d%e%f%g%h" a,b,c FormatLine 
    //                    d,e,f FormatMarker
    //                    g,h   FormatFill 
    using namespace std;
    vector<bool> vFlags { false, false, false,
        false, false, false,
        false, false};

    vector<int> vValue { 2, 1, 2, 2, 20, 1, 2, 1001 }; 
    //解析参数
    va_list args;
    va_start(args,fmt);
    for(const char* p=fmt;*p != '\0'; ++p)
    {
        switch(*p)
        {
        case '%':
            switch(*(++p))
            {
            case 'a': 
                vValue.at(0) = va_arg(args,int);
                vFlags.at(0) = true;
                continue;
            case 'b':
                vValue.at(1) = va_arg(args,int);
                vFlags.at(1) = true;
                continue;
            case 'c':
                vValue.at(2) = va_arg(args,int);
                vFlags.at(2) = true;
                continue;
            case 'd':
                vValue.at(3) = va_arg(args,int);
                vFlags.at(3) = true;
                continue;
            case 'e':
                vValue.at(4) = va_arg(args,int);
                vFlags.at(4) = true;
                continue;
            case 'f':
                vValue.at(5) = va_arg(args,int);
                vFlags.at(5) = true;
                continue;
            case 'g':
                vValue.at(6) = va_arg(args,int);
                vFlags.at(6) = true;
                continue;
            case 'h':
                vValue.at(7) = va_arg(args,int);
                vFlags.at(7) = true;
                continue;
            default:
                cout<<"===> "<<va_arg(args,int)<<endl;
                continue;
            }
        case '\n':
            continue;
        case '\t':
            continue;
        default:
            continue;
        }
    }
    va_end(args);

    //LineFormat
    if(vFlags.at(0) || vFlags.at(1) || vFlags.at(2)){
        auto attl = dynamic_cast<TAttLine*>(obj);
        if(vFlags.at(0))
            attl->SetLineColor(vValue.at(0));
        if(vFlags.at(1))
            attl->SetLineStyle(vValue.at(1));
        if(vFlags.at(2))
            attl->SetLineWidth(vValue.at(2));
    }
    //Marker Format
    if(vFlags.at(3) || vFlags.at(4) || vFlags.at(5)){
        auto attm = dynamic_cast<TAttMarker*>(obj);
        if(vFlags.at(3))
            attm->SetMarkerColor(vValue.at(3));
        if(vFlags.at(4))
            attm->SetMarkerStyle(vValue.at(4));
        if(vFlags.at(5))
            attm->SetMarkerSize(vValue.at(5));
    }
    //Fill Format 
    if(vFlags.at(6) || vFlags.at(7)){
        auto attf = dynamic_cast<TAttFill*>(obj);
        if(vFlags.at(6))
            attf->SetFillColor(vValue.at(6));
        if(vFlags.at(7))
            attf->SetFillStyle(vValue.at(7));
    }
}

void InsertLogo(TCanvas* can,int padid,double xlow=0.12,double ylow=0.82,double xup=0.36,double yup=1.0)
{
    //read the cepc logo 
    TString tutdir = gROOT->GetTutorialDir();
    tutdir.Append("/");
    tutdir.ReplaceAll("/./","/");
    auto cepclogo = TImage::Open(Form("%sCEPClogotrans01.png",tutdir.Data()));
    //std::cout<<Form("%sCEPClogo.png",tutdir.Data())<<std::endl;
    //if(cepclogo)
        //std::cout<<cepclogo->GetWidth()<<std::endl;
    auto pad = new TPad(Form("p%d",padid),Form("p%d",padid),xlow,ylow,xup,yup);
    //pad->SetLeftMargin(0.12);
    //pad->SetBorderMode(0);
    //pad->SetBorderSize(0);
    pad->SetFillStyle(4000);
    pad->Draw();
    pad->cd();
    cepclogo->Draw();
    can->cd();
}

void MoveStatBox(TH1* hist,int id,int color,double x1ndc,double x2ndc,double y1ndc,double y2ndc)
{
    auto ps = dynamic_cast<TPaveStats*>(hist->FindObject("stats"));
    if(!ps) 
    {
        std::printf("No stats obj found~ check canvas->Update()\n");
        return;
    }
    ps->SetName(Form("stats%d",id));
    ps->SetTextColor(color);
    ps->SetX1NDC(x1ndc);ps->SetX2NDC(x2ndc);
    ps->SetY1NDC(y1ndc);ps->SetY2NDC(y2ndc);
}

TColor col1(9001,98./255,42./255,29./255);//xuan_se
TColor col2(9002,255./255,33./255,33./255);//da_hong
TColor col3(9003,255./255,137./255,54./255);//ju_huang
TColor col4(9004,255./255,182./255,30./255);//teng_huang
TColor col5(9005,14./255,184./255,58./255);//cong_qing
TColor col6(9006,46./255,223./255,163./255);//yu_se 
TColor col7(9007,68./255,206./255,246./255);//lan_se 
TColor col8(9008,128./255,29./255,174./255);//qing_lian
TColor col9(9009,238./255,165./255,209./255);//ziweihua

enum colxin {xinBlack=9001, xinRed=9002, xinOrange=9003,
    xinYellow=9004, xinGreen=9005, xinCyan=9006,
    xinBlue=9007, xinPurple=9008, xinZiwei=9009 };

}

void myStyle() {

    int line_w=2;//normal size
                 //	int line_w=6;//big size

                 //std::printf("Welcome to Lansx's style Setting\n");

    TStyle *myStyle= new TStyle("myStyle","my plots style");

    myStyle->SetPalette(kCool);

    // use plain black on white colors
    myStyle->SetCanvasColor(10);
    myStyle->SetCanvasBorderMode(0);
    myStyle->SetCanvasBorderSize(2);
    myStyle->SetPadColor(10);
    myStyle->SetPadBorderMode(0);
    myStyle->SetPadBorderSize(0);
    myStyle->SetPadBottomMargin(0.1);
    myStyle->SetPadLeftMargin(0.12);
    myStyle->SetPadRightMargin(0.05);
    myStyle->SetPadTopMargin(0.07);
    myStyle->SetLineWidth(line_w);//change tick width
    myStyle->SetFuncColor(kRed);
    myStyle->SetHistLineColor(kBlue);
    //myStyle->SetPadTickX(1);
    //myStyle->SetPadTickY(1);
    myStyle->SetTickLength(0.02,"X");
    myStyle->SetTickLength(0.02,"Y");
    myStyle->SetPadGridX(0);
    myStyle->SetPadGridY(0);
    //myStyle->SetGridColor(18);
    myStyle->SetFrameFillStyle(4000);
    myStyle->SetFrameLineWidth(line_w);
    myStyle->SetFrameBorderSize(1);
    myStyle->SetFrameBorderMode(0);
    myStyle->SetFrameFillColor(10);
    //gStyle->SetFrameLineStyle(1);
    myStyle->SetLegendBorderSize(0);
    myStyle->SetLegendFillColor(0);
    myStyle->SetLegendFont(22);
    myStyle->SetLegendTextSize(0.04);

    //TLegend::SetFillStyle(1001);

    // set the paper & margin sizes
    myStyle->SetPaperSize(20,26);

    int font = 22;
    //int font = 132;
    // use large Times-Roman fonts
    myStyle->SetTextFont(font);
    myStyle->SetTextSize(0.03);
    myStyle->SetLabelFont(font,"xyz");
    myStyle->SetTitleFont(font,"xyz");
    myStyle->SetLegendFont(font);
    myStyle->SetStatFont(font);

    myStyle->SetLabelSize(0.04,"xyz");//D=0.04
    myStyle->SetTitleSize(0.05,"xyz");//D=0.02
    myStyle->SetTitleSize(0.05,"");//main title

    myStyle->SetLabelOffset(0.01,"xyz");//D=0.005
    myStyle->SetTitleOffset(0.9,"x");
    myStyle->SetTitleOffset(1.0,"y");
    myStyle->SetTitleOffset(0.8,"z");
    //TGaxis::SetMaxDigits(3);

    // use bold lines and markers
    myStyle->SetMarkerStyle(20);
    myStyle->SetHistLineWidth(2);
    myStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

    // get rid of X error bars and y error bar caps
    //myStyle->SetErrorX(0.001);

    // do not display any of the standard histogram decorations
    myStyle->SetTitleX(0.5);
    myStyle->SetTitleAlign(23);
    //myStyle->SetTitleColor(0);
    myStyle->SetTitleStyle(0);
    myStyle->SetTitleBorderSize(0);
    //myStyle->SetOptTitle(0);
    myStyle->SetOptStat(1);
    myStyle->SetOptFit(111);


    myStyle->SetStatColor(10);

    gROOT->SetStyle("myStyle");
    gROOT->ForceStyle();

}


void globleStyle() {

    //============================================================
    // 
    //          Make graphs pretty
    // 
    //============================================================
    std::cout<<"gStyle mode requested!!!"<<std::endl;

    //int font = 42;
    int font = 132;

    gStyle->SetOptTitle(1);
    gStyle->SetOptDate(0);
    gStyle->SetOptStat(0);
    gStyle->SetStatColor(10);
    //gStyle->SetOptFit(0);
    gStyle->SetStatH(0.17);
    gStyle->SetStatW(0.17);
    gStyle->SetPalette(1,0);
    gStyle->SetTextFont(font);
    gStyle->SetTextSize(0.055);
    //gStyle->SetErrorX(1);
    gStyle->SetEndErrorSize(4);
    gStyle->SetDrawBorder(0);

    gStyle->SetCanvasDefH(600);
    gStyle->SetCanvasDefW(800);
    gStyle->SetCanvasColor(10);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetCanvasBorderSize(2);
    gStyle->SetPadColor(10);
    gStyle->SetPadBorderMode(0);
    gStyle->SetPadBorderSize(0);
    gStyle->SetPadBottomMargin(0.12);
    gStyle->SetPadLeftMargin(0.12);
    gStyle->SetPadRightMargin(0.10);
    gStyle->SetPadTopMargin(0.08);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetTickLength(0.02,"X");
    gStyle->SetTickLength(0.02,"Y");
    gStyle->SetPadGridX(0);
    gStyle->SetPadGridY(0);
    gStyle->SetGridColor(18);
    gStyle->SetLineWidth(2);
    gStyle->SetFrameFillStyle(4000);
    gStyle->SetFrameLineWidth(2);
    gStyle->SetFrameBorderSize(2);
    gStyle->SetFrameBorderMode(0);
    gStyle->SetFrameFillColor(10);
    //gStyle->SetFrameLineStyle(1);

    gStyle->SetNdivisions(510,"X");
    gStyle->SetNdivisions(510,"Y");
    gStyle->SetLabelSize(0.04,"X");
    gStyle->SetLabelSize(0.04,"Y");
    gStyle->SetLabelFont(font,"X");
    gStyle->SetLabelFont(font,"Y");
    gStyle->SetLabelOffset(0.01,"X");
    gStyle->SetLabelOffset(0.01,"Y");
    gStyle->SetTitleOffset(1.8,"X");
    gStyle->SetTitleOffset(1.2,"Y");
    gStyle->SetTitleOffset(0.);
    //gStyle->SetPadRightMargin(.2); 
    gStyle->SetTitleSize(0.05,"X");
    gStyle->SetTitleSize(0.05,"Y");
    gStyle->SetTitleSize(0.05,"Z");
    gStyle->SetTitleFont(font,"X");
    gStyle->SetTitleFont(font,"Y");
    gStyle->SetTitleFont(font,"Z");

    // COPY FROM MYSTYLE()
    // gStyle->SetTitleColor(3);
    // gStyle->SetTitleX(0.07);
    // gStyle->SetTitleAlign(23);
    // gStyle->SetTitleStyle(0);
    // gStyle->SetTitleBorderSize(0);
}

// set color display, raibow, grayscale...
void set_color_env(){

    const Int_t NRGBs = 5;
    const Int_t NCont = 99;

    Int_t fcol;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    fcol = TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
    //SetPalette has been called in the above function, color style will
    //be set according to your own rgb definition if called

    //grayscale
    /*
       double dcol = 1/double(NRGBs);
       double grey = 1;

       for(int j = 0; j < NRGBs; j++){  
    // ...... Define color with RGB equal to : gray, gray, gray .......
    stops[j]=double(j)/double(NRGBs-1);
    red[j]=grey;
    blue[j]=grey;
    green[j]=grey;

    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    */	

    TString Red1 =  "#FFCC00";
    TString Red2 =  "#FF9900";
    TString Red3 =  "#FF6600";
    TString Red4 =  "#FF3300";
    TString Red5 =  "#FF0000";

    TString Blue1 =  "#3300FF";
    TString Blue2 =  "#0000FF";
    TString Blue3 =  "#0033FF";
    TString Blue4 =  "#0066FF";
    TString Blue5 =  "#0099FF";
    TString Blue6 =  "#00CCFF";
    TString Blue7 =  "#00FFFF";
    TString Blue8 =  "#00FFCC";

    TString Green1 =  "#006633";
    TString Green2 =  "#006600";
    TString Green3 =  "#009933";
    TString Green4 =  "#009900";
    TString Green5 =  "#339900";
    TString Green6 =  "#00CC33";
    TString Green7 =  "#00CC00";
    TString Green8 =  "#33CC00";
    TString Green9 =  "#00FF00";

    TString Oran1 = "#FF3300";
    TString Oran2 = "#FF6600";
    TString Oran3 = "#FF6633";
    TString Oran4 = "#FF9900";
    TString Oran5 = "#FF9933";
    TString Oran6 = "#FF9966";  

    TString SkyBlue = "#00CCFF";
    TString SeaBlue = "#0099FF";
    TString SadBlue = "#009999";
    TString LakeBlue = "#0099CC";
    TString DarkBlue = "#000099";

    TString Purp1 = "#CC33CC";
    TString Purp2 = "#9900FF";
    TString Purp3 = "#CC00FF";
    TString Purp4 = "#FF00FF";
    TString Purp5 = "#FF33FF";
    TString Purp6 = "#FF33CC";   
    TString Purp7 = "#FF66FF";
    //how to use the color defined above --->  SetLineColor(TColor::GetColor(SkyBlue)) or SetLineColor(TColor::GetColor(SkyBlue.Data()))

}

void myrootlogon() {

    //load your system wise	root settings
    //  globleStyle();
    myStyle();
    //  set_color_env();


}
