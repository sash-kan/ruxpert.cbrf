curdate = $(shell date +%F)
mrrf_reqbody = <$(@) xmlns="http://web.cbr.ru/">\
  <fromDate>2012-01-01</fromDate>\
  <ToDate>$(curdate)</ToDate>\
 </$(@)>
req = '<?xml version="1.0" encoding="utf-8"?>\
 <soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">\
	<soap:Body>\
	 $($(@)_reqbody)\
	</soap:Body>\
 </soap:Envelope>'
link = http://www.cbr.ru/DailyInfoWebServ/DailyInfo.asmx
head1 = 'Content-Type: text/xml; charset=utf-8'
head2 = 'SOAPAction: http://web.cbr.ru/$@'
cook = cookie.file
command = wget -q -O - --post-data=$(req) $(link) \
 --header $(head1) --header $(head2) \
 --keep-session-cookies --save-cookies=$(cook) --load-cookies=$(cook)

%.parsed: %.xml
	cat $< | xml2 > $@

%.xml:
	$(MAKE) -f $(lastword $(MAKEFILE_LIST)) -s $* 2>/dev/null > $@

mrrf:
	$(command)

clean::
	-rm *.xml *.parsed $(cook)
