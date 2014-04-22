cl /MD /O2 /W3 /c /DLUA_BUILD_AS_DLL *.c
del *.o
ren lua.obj lua.o
ren luac.obj luac.o
ren print.obj print.o
link /DLL /IMPLIB:lua5.2.3.lib /OUT:lua5.2.3.dll *.obj
link /OUT:lua.exe lua.o lua5.2.3.lib
lib /out:lua5.2.3-static.lib *.obj
link /OUT:luac.exe luac.o print.o lua5.2.3-static.lib