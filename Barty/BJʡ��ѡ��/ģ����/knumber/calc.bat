@echo off
if "%1"=="" goto loop
copy knumber%1.in knumber.in >nul
echo Problem Test
echo Data %1
time<enter
knumber
time<enter
fc knumber.out knumber%1.out
del knumber.in
del knumber.out
pause
goto end
:loop
for %%i in (0 1 2 3 4 5 6 7 8 9) do call %0 %%i
:end