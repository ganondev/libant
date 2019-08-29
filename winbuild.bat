pushd C:
call "C:\Program Files (x86)\Microsoft Visual C++ Build Tools\vcbuildtools.bat"
popd
cl /LD c\antalgo.c c\anttype.c -Ic
exit %errorlevel%
