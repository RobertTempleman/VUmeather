cd ..
RMDIR /S /Q temp
mkdir temp
robocopy /E sw temp\sw
cd temp
attrib /S -R -H -S *.*
del /q /S *.ipch
del /q /S *.obj
del /q /S *.pch
del /q /S *.pdb
del /q /S *.ilk
del /q /S *.exe
del /q /S *.sdf
del /q /S *.idb
del /q /S *.tlog
del /q /S *.bmp
del /q /S *.scc
del /q /S *.opensdf
del /q /S *.vspscc
del /q /S *.vssscc
"C:\Program Files\7-Zip\7z.exe" a "metal_deturd_%date:~-4,4%_%date:~-10,2%_%date:~-7,2%_%time:~0,2%h%time:~3,2%m_fh.7z" sw
RMDIR /S /Q sw
cd ..
move temp\* .
RMDIR /S /Q temp
