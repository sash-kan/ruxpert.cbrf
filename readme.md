импорт статистики по внешнему долгу с сайта цбрф для вставки на страницу
http://ruxpert.ru/Статистика:Внешний_долг_России

1. проверьте актуальность ссылки в первой строке файла GNUmakefile, в
переменной src
2. выполните команду 'make'
3. результат — в файле result
4. сравните его с прилагаемым файлом 20130114.result: после каждой даты должно
идти пять чисел
5. если чисел меньше, сверьте ключевые слова для поиска нужных строк в таблице
(вторая строка файла GNUmakefile, переменная lines) с самой таблицей (файл
srctable). ключевые слова ищутся в самом начале строки, сразу после символа
«вертикальная черта».
6. для удаления всех сгенерированных файлов выполните команду 'make clean'