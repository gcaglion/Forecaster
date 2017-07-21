Tester-Multi launches tester.exe with combinations of different parameter values

	MT4 Setup:
	create terminal.cmd in the same ProgramFiles(x86) dir as terminal.exe, with the following:
		set ORACLE_HOME=%ORACLE_HOME2%
		set PATH=%ORACLE_HOME%\bin
		start /b .\terminal
