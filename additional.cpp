#include <iostream>
#include <fstream>
#include "defines.hpp"
using namespace std;

string convert(string got, int font);
string scanHuman();
string scanTestFile();
string getEndTemplate();
string getBeginTemplate();
string getHeader();

int x = XBASE;
int y = YBEGIN;

string scanHuman()
{
    string line;
    string add = getHeader();
    while (true)
    {
        getline(cin, line);
        if (line == "OVER") break;
        add += ("\n" + convert(line, FONT));
    }
    return add;
}

string scanTestFile()
{
    string line;
    string add = getHeader();
    ifstream is("test.txt");
    if (is.is_open())
    {
        while (true)
        {
            getline(is, line);
            if (line == "OVER") break;
            add += ("\n" + convert(line, FONT));
        }
    }
    else cout << "is error";
    return add;
}

string getBeginTemplate()
{
    ifstream is("example.pdf");
    string line;
    string temp;
    if (is.is_open())
    {
        for (int i = 0; i < 36; i ++)
        {
            getline(is, line);
            temp += ("\n" + line);
        }
    }
    else cout << "is error";
    return temp;
}

string getEndTemplate()
{
    ifstream is("example.pdf");
    string line;
    string temp;
    if (is.is_open())
    {
        for (int i = 0; i < 41; i ++) {getline(is, line);}
        for (int i = 41; i < 58; i ++)
        {
            getline(is, line);
            temp += ("\n" + line);
        }
    }
    else cout << "is error";
    return temp;
}

string convert(string got, int font)
{
    string type = got.substr(0,5);
    string body = got.substr(5, got.size());

    if (type == "word:")    //common strings
    {
        string strY = to_string(y);
        y -= 20;
        
        return ("BT /F1 " + to_string(FONT) + " Tf " + to_string(x) 
            + " " + strY + " Td (" + body + ") Tj ET");
    }

    if (type == "bwor:")    //header strings (bigger font)
    {
        y -= 10;
        string strY = to_string(y);
        y -= 20;

        return ("BT /F1 " + to_string(BIGFONT) + " Tf " + to_string(x)
            + " " + strY + " Td (" + body + ") Tj ET");
    }

    if (type == "cwor:")    //custom font word
    {
        y -= 10;
        string strY = to_string(y);
        y -= 20;

        return ("BT /F1 " + to_string(font) + " Tf " + to_string(x)
            + " " + strY + " Td (" + body + ") Tj ET");
    }

    else if (type == "line:")   //full-size underline
    {
        string strY = to_string(y);
        y -= 30;
        return ("BT 30 " + strY + " m 470 " + strY + " l h S ET");
    }

    return "";
}

string getHeader()
{
    string toRet;
    toRet += convert("cwor:Boot record", HEADERFONT);
    return toRet;
}