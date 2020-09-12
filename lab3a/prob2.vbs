Option Explicit
Dim objShell
Dim pathName
set objShell = Wscript.CreateObject ("Wscript.Shell")
pathName = "C:\BELSTU\OS\text.txt"
objShell.Run pathName
