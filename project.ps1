param(
    [string]$mFile="data",
    [string]$mExtension=".txt",
    [string]$mKey="KEY"
    )
#Script to test project
g++ -std=c++14 EnCo.cpp -o EnCo.exe
#-- Processing file
$pro = './EnCo.exe'
$ArgsList = " -file "+"$($mFile)$($mExtension)"+" -key "+$mKey+" -e -com"
Start-Process $pro -ArgumentList $ArgsList -Wait -NoNewWindow
#--
Start-Sleep -s 2
#-- Re-Processing file
$pro = './EnCo.exe'
$ArgsList = " -file "+"$($mFile)_e_com$($mExtension)"+" -key "+$mKey+" -d -decom"
Start-Process $pro -ArgumentList $ArgsList -Wait -NoNewWindow
#--
Remove-Item -path "$($mFile)_e_com$($mExtension)" -recurse -Force
#--
Remove-Item -path EnCo.exe -recurse -Force
notepad "$($mFile)_e_com_d_decom$($mExtension)"