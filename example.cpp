#include <cstdlib>
#include "pdflib.cpp"

void testTemplate(char* toRet);

int main(int argc, char* argv[])
{
    char add[8192];
    testTemplate(add);
    insertPDF("output.pdf", add);
    system("xreader output.pdf");
    return 0;
}

void testTemplate(char* toRet)
{
    appendString(toRet, "fstr:Boot record", 24);
    appendString(toRet, "bstr:Starting...");
    appendString(toRet, "line:");
    appendString(toRet, "cstr:Is anybody here?");
    appendString(toRet, "subs:First item");
    appendString(toRet, "subs:Second item");
    appendString(toRet, "subs:Third item");
    appendString(toRet, "cstr:Russian isn't allowed");
    appendString(toRet, "line:");
    appendString(toRet, "bstr:Shutdown...");
}
