"C:\Program Files (x86)\XM UK MT4\metaeditor.exe" /compile:MyForecaster.mq4 /log
type MyForecaster.log > MyForecaster.utf8
copy MyForecaster.ex4 C:\Users\gcaglion\appdata\roaming\MetaQuotes\terminal\61007F75C6EC7CED9A269B292061D7A1\MQL4\Experts\
FOR /F "tokens=1,2 delims=: " %%G IN (MyForecaster.utf8) DO (
	@echo %%G %%H
	if %%G==Result (exit %%H)
)
