@REM run as Administrator
@echo off
cd /d %~dp0
set DOWNLOADS_DIR=%USERPROFILE%\Downloads
set DOWNLOADS_DIR_LINUX=%DOWNLOADS_DIR:\=/%


SET PATH=^
%DOWNLOADS_DIR%\avr8\avr8;^
%DOWNLOADS_DIR%\avr8\avr8\avr8-gnu-toolchain\bin;^
%DOWNLOADS_DIR%\PortableGit\usr\bin;


avr-objdump.exe -D -m avr -b ihex -M avr6 EIE3105_ATmega328P_Application.hex > EIE3105_ATmega328P_Application_objdump.txt
pause
