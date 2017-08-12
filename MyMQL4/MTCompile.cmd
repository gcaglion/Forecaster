"C:\Program Files (x86)\XM UK MT4\metaeditor.exe" /compile:C:\Users\gcaglion\appdata\roaming\MetaQuotes\terminal\61007F75C6EC7CED9A269B292061D7A1\MQL4\Experts\MyForecaster.mq4 /log
type C:\Users\gcaglion\appdata\roaming\MetaQuotes\terminal\61007F75C6EC7CED9A269B292061D7A1\MQL4\Experts\MyForecaster.log > C:\Users\gcaglion\appdata\roaming\MetaQuotes\terminal\61007F75C6EC7CED9A269B292061D7A1\MQL4\Experts\MyForecaster.utf8
FOR /F "tokens=1,2 delims=: " %%G IN (C:\Users\gcaglion\appdata\roaming\MetaQuotes\terminal\61007F75C6EC7CED9A269B292061D7A1\MQL4\Experts\MyForecaster.utf8) DO (
	@echo %%G %%H
	if %%G==Result (exit %%H)
)
