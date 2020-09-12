Set fso=WScript.CreateObject("Scripting.FileSystemObject")
Set file=fso.CreateTextFile("c:\BELSTU\OS\EXCEL.bat")
file.WriteLine("start Excel.exe")
file.Close
Set newObj = CreateObject("WScript.Shell")
newObj.Run "c:\BELSTU\OS\EXCEL.bat"