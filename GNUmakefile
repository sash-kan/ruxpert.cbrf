src = "http://www.cbr.ru/statistics/print.aspx?file=credit_statistics/debt_new.htm&pid=svs&sid=itm_34989"
words = Organy Central Banki Prochie Vsego

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
res2: res1
	sed -r 's/\| *([0-9])/|\1/g' $< > $@

# результат — в виде wiki-разметки для вставки сюда:
# http://ruxpert.ru/Статистика:Внешний_долг_России
result: res2
	nf=$$(($$(awk -F '|' '{print NF; exit}' $<)-1)); for i in $$(seq 3 $$nf); do echo '|-'; awk -F '|' '{print $$'$$i'}' $< | sed '1s/^/! /;1!s/^/| /'; echo '|'; done > $@

clean:
	-rm res* srctable

.PHONY: clean
