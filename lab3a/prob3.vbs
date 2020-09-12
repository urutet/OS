Set fso=WScript.CreateObject("Scripting.FileSystemObject")
Set file=fso.OpenTextFile("c:\BELSTU\OS\FILE1.txt")
Set fileIn=fso.CreateTextFile("c:\BELSTU\OS\FILE2.txt", ForWriting)
do until file.AtEndOfStream
str = file.ReadLine
fileIn.WriteLine(str)
loop
file.Close
fileIn.close
