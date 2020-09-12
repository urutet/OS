'Processor Information

On Error Resume Next
Message =""
strComputer = "."
Set objWMIService = GetObject("winmgmts:" _
    & "{impersonationLevel=impersonate}!\\" & strComputer & "\root\cimv2")

Set colItems = objWMIService.ExecQuery("Select * from Win32_Processor")
Set fso = WScript.CreateObject("Scripting.FileSystemObject")
Set file = fso.CreateTextFile("C:\BELSTU\OS\ProcessorInfo.txt")

For Each objItem in colItems
    Message=Message & "Speed: " & objItem.CurrentClockSpeed & vbCrLf  
    Message=Message & "Architecture: " & objItem.DataWidth& vbCrLf
    Message=Message & "Description: " & objItem.Description& vbCrLf
    Message=Message & "Family: " & objItem.Family& vbCrLf
    Message=Message & "Cache size: " & objItem.L2CacheSize& vbCrLf
    Message=Message & "Current load percentage: " & objItem.LoadPercentage& vbCrLf
    Message=Message & "Manufacturer: " & objItem.Manufacturer& vbCrLf
    Message=Message & "Processor ID: " & objItem.ProcessorId& vbCrLf
	Message=Message & "Vesrion: " & objItem.Version & vbCrLf
   
Next
	file.WriteLine(Message)
	MsgBox Message
