:: note: My system cc defaults are -W -Wall -ansi -pedantic -O2
:: note: This executes with 4dos under W98
cc -c ggets.c
if errorlevel 1 goto fail

cc -o tggets.exe ggets.o tggets.c
if errorlevel 1 goto fail

cc -o freverse.exe ggets.o freverse.c
if errorlevel 1 goto fail

tggets malloc.xrf >junk
diff -q junk malloc.xrf
if errorlevel 1 goto fail

tggets nocrend.txt >junk
diff -q junk nocrend.cpy
if errorlevel 1 goto fail

tggets nocrend1.txt >junk
diff -q junk nocrend1.cpy
if errorlevel 1 goto fail

tggets nocrend2.txt >junk
diff -q junk nocrend2.cpy
if errorlevel 1 goto fail

freverse <ggets.c >junk1
freverse <junk1 >junk2
diff -q junk2 ggets.c
if errorlevel 1 goto fail

echo test succeeded
goto done

:fail
echo test failed

:done
