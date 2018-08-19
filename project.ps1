param(
    [string]$mFile="data",
    [string]$mExtension=".txt",
    [string]$mKey="KEY"
    )
#Script is to test project only.
#Script works strickly on Windows 7 and above
#Project is compataible with any system with C++14 compiler
g++ -std=c++14 EnCo.cpp -o EnCo.exe
#-- Processing file
$pro = './EnCo.exe'
$ArgsList = " -f "+"$($mFile)$($mExtension)"+" -k "+$mKey+" -e"
Start-Process $pro -ArgumentList $ArgsList -Wait -NoNewWindow
#--
Start-Sleep -s 2
#-- Re-Processing file
$pro = './EnCo.exe'
$ArgsList = " -f "+"$($mFile)-e$($mExtension)"+" -k "+$mKey+" -d"
Start-Process $pro -ArgumentList $ArgsList -Wait -NoNewWindow
#--
Remove-Item -path "$($mFile)-e$($mExtension)" -recurse -Force
#--
Remove-Item -path EnCo.exe -recurse -Force
