Attribute VB_Name = "Module1"
Sub GenerateAllocation()
    ChDir ThisWorkbook.Path
    Dim myInput As String, myResult As String
    myInput = "input.dat"
    myResult = "result.dat"
    
    Dim stuNum As Long '# of students
    stuNum = 0
    Do While Cells(stuNum + 2, 1) <> ""
        Cells(stuNum + 2, 2) = ""
        stuNum = stuNum + 1
    Loop
    
    'check data
    Dim istu As Integer, icol As Integer
    For istu = 1 To stuNum
        For icol = 3 To 35
            If Cells(istu + 1, icol) = "" Then
                MsgBox "Incomplete sheet!"
                Exit Sub
            End If
        Next
    Next
    
    'write
    If Dir(myInput) <> "" Then Kill myInput
    Open myInput For Binary As #1
    
    Put #1, , stuNum
    Dim i As Integer, j As Integer
    For i = 1 To stuNum
        For j = 1 To stuNum
            Put #1, , Grade(i, j)
        Next
    Next

    Close #1
    
    Dim calctime As String
    calctime = InputBox(stuNum & " students in total." & vbCrLf & "Please input the times of calculations:", "Dorm Allocating", 20)
    
    'call external procedure
    Dim WSH As Object, wExec As Object, result As String
    Set WSH = CreateObject("WScript.Shell")
    Set wExec = WSH.exec("dorm_allocator.exe " & myInput & " " & calctime)
    result = wExec.StdOut.ReadAll
    If result <> "" Then MsgBox result
    
    'read
    If wExec.ExitCode <> 0 Or Dir(myResult) = "" Then
        MsgBox "Procedure failed unexpectedly!"
        Exit Sub
    End If
    Open myResult For Binary As #2
    
    Dim stu As Long, dorm As Integer
    dorm = 1
    
    Do While Seek(2) < LOF(2)
        Get #2, , stu
        If stu <> 0 Then
            Cells(stu + 1, 2) = dorm
        Else
            dorm = dorm + 1
        End If
    Loop
    
    Close #2
    
    Kill myInput
    Kill myResult
End Sub

Function Grade(stuA As Integer, stuB As Integer) As Long 'A对B的评价
    If stuA = stuB Then
        Grade = 1000 '自己对自己设为最大值
        Exit Function
    End If
    
    '电脑游戏
    Grade = (Cells(stuB + 1, 6) * Cells(stuA + 1, 11) + 1) * Cells(stuA + 1, 33)
    '外放音乐
    Grade = Grade + (Cells(stuB + 1, 7) * Cells(stuA + 1, 12) + 1) * Cells(stuA + 1, 34)
    '共用物品
    Grade = Grade + (Cells(stuB + 1, 8) * Cells(stuA + 1, 13) + 1) * Cells(stuA + 1, 35)
    
    '入睡时间
    Dim deltaT As Integer
    deltaT = Cells(stuB + 1, 9) - Cells(stuA + 1, 14)
    Select Case deltaT
    Case -9, -8, -7, -6, -5, -4
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 15) / 5)
    Case -3
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 16) / 5)
    Case -2
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 17) / 5)
    Case -1
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 18) / 5)
    Case 0
        Grade = Grade + Cells(stuA + 1, 32)
    Case 1
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 19) / 5)
    Case 2
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 20) / 5)
    Case 3
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 21) / 5)
    Case 4, 5, 6, 7, 8, 9
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 22) / 5)
    End Select
    
    '起床时间
    deltaT = Cells(stuB + 1, 10) - Cells(stuA + 1, 23)
    Select Case deltaT
    Case -9, -8, -7, -6, -5, -4
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 24) / 5)
    Case -3
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 25) / 5)
    Case -2
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 26) / 5)
    Case -1
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 27) / 5)
    Case 0
        Grade = Grade + Cells(stuA + 1, 32)
    Case 1
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 28) / 5)
    Case 2
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 29) / 5)
    Case 3
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 30) / 5)
    Case 4, 5, 6, 7, 8, 9
        Grade = Grade + Cells(stuA + 1, 32) * (1 - Cells(stuA + 1, 31) / 5)
    End Select
End Function
