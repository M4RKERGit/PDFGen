# Мини - библиотека для генерации простых PDF-отчетов и списков, ориентирована на микроконтроллеры без использования динамического выделения памяти

## Пример работы - файл example.cpp

### Как это работает:

* Копируем файл pdflib.cpp себе в проект
* include "pdflib.cpp"
* Создаем буфер (в примере 8192 символов, создавайте соразмерно тому кол-ву информации, что может в него попасть)
* Функция appendString ({буфер}, {строка}, {шрифт}) заполняет буфер строкой, форматированной в PDF Stream, вызываем для добавления строки или линии, в примере заполнение происходит в функции testTemplate({буфер})
* После того, как было добавлено все нужное содержимое, вызываем функцию insertPDF({имя файла}, {буфер})
* You're breathtaking!

### Справка по добавлению строк:

1) Все строки должны быть переданы в функцию appendString в формате "тип:содержимое"
2) Доступные типы содержимого:

* cstr - обычная текстовая строка, использует стандартный шрифт (12)
* bstr - текстовая строка с увеличенным шрифтом (18)
* fstr - текстовая строка с кастомным шрифтом, размер шрифта указывается последним аргументом appendString
* subs - текстовая строка с отступом, можно использовать для составления списков, уточнений или сносок
* line - подчеркивающая линия, содержимое можно не указывать

Функционал может быть расширен в будущем, подробнее смотри в реализации функции convert() файла pdflib.cpp
