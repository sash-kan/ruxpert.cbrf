src = "http://www.cbr.ru/statistics/print.aspx?file=credit_statistics/debt_new.htm&pid=svs&sid=itm_34989"
words = Organy Central Banki Prochie Vsego

xml2 := $(shell which xml2)
ifeq (,$(xml2))
$(error для работы нужна программа xml2. обычно она входит в одноимённый пакет)
endif

all: result

# получаем страницу с сайта цбрф в удобоваримом виде
srctable:
	links -dump $(src) > $@

# вырезаем таблицу
res0: srctable
	sed -n '/^+---/,/^+---/p' $< > $@

# сначала берём вторую строку — с датами
# затем те строки, которые начинаются с ключевых слов,
# перечисленных в переменной words (см. начало файла)
res1: res0
	sed -n '2,/^.---/p' $< | sed '$$d' > $@
	for i in $(words); do sed -n '/^|'$$i'/,/^.---/p' $< | sed '$$d' | sed '$$!d'; done >> $@

# удаляем лишние пробелы в столбцах перед числами
# и преобразуем даты из "dd.mm.yyyy" в "yyyy-mm-dd"
res2: res1
	sed -r 's/\| *([0-9])/|\1/g;1s/([0-9]{2})\.([0-9]{2})\.([0-9]{4})/\3-\2-\1/g' $< > $@

# результат — в виде wiki-разметки для вставки сюда:
# http://ruxpert.ru/Статистика:Внешний_долг_России
result: res2 mrrf.parsed
	nf=$$(($$(awk -F '|' '{print NF; exit}' $<)-1)); \
for i in $$(seq 3 $$nf); do echo '|-'; \
awk -F '|' '{print $$'$$i'}' $< | sed '1s/^/! /;1!s/^/| /'; \
date=$$(awk -F '|' '{print $$'$$i';exit}' $<); \
sed -n '/D0='$$date'/,/p1=/p' $$(echo $(word 2,$?)) | sed -r '1d;s/^.*=/| /;s/([0-9]{3})\.00$$/ \1/'; \
done > $@

clean::
	-rm res* srctable

.PHONY: clean

include mrrf.inc
