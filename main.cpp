#include "additional.cpp"
using namespace std;

int main(int argc, char* argv[])
{
    cout << "Start" << endl;
    string begTemp = getBeginTemplate();
    string endTemp = getEndTemplate();
    //string add = scanHuman();
    string add = scanTestFile();

    ofstream fs("output.pdf");
    if (fs.is_open()) {fs << begTemp << add << endTemp;}
    else cout << "fs error";

    return 0;
}