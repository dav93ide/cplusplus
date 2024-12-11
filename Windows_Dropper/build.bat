@ECHO OFF

cl.exe /nologo /0x /MT /W0 /GS- /DNDEBUG /Tp dropper.cpp /link /OUT:dropper.exe /SUBSYSTEM:WINDOWS

rem
del *.obj