#include <cstdlib>
#include <cstring>
#include <cstdio>

#define XBASE 30
#define YBEGIN 780
#define FONT 12
#define BIGFONT 18

void insertPDF(const char* fileName, char* add);
void appendString(char* toRet, const char* add, int font);
void convert(char* toRet, const char* got, int font);
void constructString(char* toRet, char* body, int font, int y, int type);
void constructSubString(char* toRet, char* body, int y, int type);
void constructLine(char* toRet, int y);
void substring(char* toRet, const char* arr, int begin, int end);

int x = XBASE;
int y = YBEGIN;

const char* beginTemplate = "%PDF-1.7\r\n%¥±ë\r\n\r\n1 0 obj\r\n  << /Type /Catalog\r\n     /Pages 2 0 R\r\n  >>\r\nendobj\r\n\r\n2 0 obj\r\n  << /Type /Pages\r\n     /Kids [3 0 R]\r\n     /Count 1\r\n     /MediaBox [0 0 500 800]\r\n  >>\r\nendobj\r\n\r\n3 0 obj\r\n  <<  /Type /Page\r\n      /Parent 2 0 R\r\n      /Resources\r\n       << /Font\r\n           << /F1\r\n               << /Type /Font\r\n                  /Subtype /Type1\r\n                  /BaseFont /Times-Roman\r\n               >>\r\n           >>\r\n       >>\r\n      /Contents 4 0 R\r\n  >>\r\nendobj\r\n\r\n4 0 obj\r\n  << /Length 150 >>\r\nstream\r\n";
const char* endTemplate = "\r\nendstream\r\nendobj\r\n\r\nxref\r\n0 5\r\n0000000000 65535 f \r\n0000000018 00000 n \r\n0000000077 00000 n \r\n0000000178 00000 n \r\n0000000457 00000 n \r\ntrailer\r\n  <<  /Root 1 0 R\r\n      /Size 5\r\n  >>\r\nstartxref\r\n565\r\n";

void insertPDF(const char* fileName, char* add)
{
    FILE* f = fopen(fileName, "w");
    fprintf(f, "%s%s%s", beginTemplate, add, endTemplate);
    fclose(f);
}

void appendString(char* toRet, const char* add, int font = 12)
{
    char buf[256] = {0};
    memset(buf, 0, 256);
    convert(buf, add, font);
    strcat(toRet, "\n");
    strcat(toRet, buf);
}

void convert(char* toRet, const char* got, int font)
{
    char type[5] = {0};
    char body[256] = {0};
    memset(toRet, 0, 256);
    substring(type, got, 0, 4);
    substring(body, got, 5, strlen(got));
    
    if (strcmp(type, "cstr") == 0)    //обычный текст
    {
        constructString(toRet, body, font, y, 0);
        y -= 20;
        return;
    }

    if (strcmp(type, "bstr") == 0)    //текст с увеличенным шрифтом
    {
        constructString(toRet, body, font, y-10, 1);
        y -= 30;
        return;
    }

    if (strcmp(type, "fstr") == 0)    //текст с кастомным шрифтом
    {
        if (font > 40) y -= 10;
        if (font < 10) y += 10;
        constructString(toRet, body, font, y-10, 2);
        y -= 30;
        return;
    }

    if (strcmp(type, "subs") == 0)    //текст с отступом вправо
    {
        constructSubString(toRet, body, y, 2);
        y -= 20;
        return;
    }

    if (strcmp(type, "line") == 0)   //подчеркивающая линия
    {
        constructLine(toRet, y);
        y -= 30;
        return;
    }
    printf("\nОшибка типа содержимого: %s\n", type);
}

void constructString(char* toRet, char* body, int font, int y, int type)
{
    if (type == 0) font = FONT;
    else if (type == 1) font = BIGFONT;
    sprintf(toRet, "BT /F1 %d Tf %d %d Td (%s) Tj ET", font, x, y, body);
}

void constructSubString(char* toRet, char* body, int y, int type)
{
    sprintf(toRet, "BT /F1 %d Tf %d %d Td (%s) Tj ET", FONT, x+20, y, body);
}

void constructLine(char* toRet, int y)
{
    sprintf(toRet, "BT 30 %d m 470 %d l h S ET", y, y);
}

void substring(char* toRet, const char* arr, int begin, int end)
{
    for (int i = 0; i < end; i++) toRet[i] = *(arr + begin + i);
    toRet[end] = 0;
}