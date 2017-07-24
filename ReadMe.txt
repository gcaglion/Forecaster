
	MT4 Setup:
	create terminal.cmd in the same ProgramFiles(x86) dir as terminal.exe, with the following:
		set ORACLE_HOME=%ORACLE_HOME2% (where %ORACLE_HOME2% is a 32-bit Oracle Home)
		set PATH=%ORACLE_HOME%\bin
		start /b .\terminal
