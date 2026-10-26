@echo off
set TEST=%1
if "%TEST%"=="" set TEST=sp1-1

if not exist debug mkdir debug

gcc -Wall -g -o debug\s1-01.exe main.c
if errorlevel 1 (
    echo Erreur de compilation
    exit /b 1
)

debug\s1-01.exe < debug\in-%TEST%.txt > debug\res-%TEST%.txt

fc debug\res-%TEST%.txt debug\out-%TEST%.txt > nul
if errorlevel 1 (
    echo [%TEST%] DIFFERENCES :
    fc debug\res-%TEST%.txt debug\out-%TEST%.txt
) else (
    echo [%TEST%] OK
)