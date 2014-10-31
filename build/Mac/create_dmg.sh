#!/bin/bash

#
# Удалить старый образ
#
rm ./Scenarist.dmg

#
# сформировать app-файл
#
~/Qt/5.3/clang_64/bin/macdeployqt ../Release/bin/Scenarist/Scenarist.app

#
# скопировать в него библиотеки
#
# hunspell
#
cp ../Release/libs/hunspell/libhunspell.1.dylib ../Release/bin/Scenarist/Scenarist.app/Contents/Frameworks/
#
# quazip
#
cp -H ../Release/libs/quazip/libquazip.1.dylib ../Release/bin/Scenarist/Scenarist.app/Contents/Frameworks/
#
# rtf-qt
#
cp ../Release/libs/rtf-qt/librtf-qt.1.dylib ../Release/bin/Scenarist/Scenarist.app/Contents/Frameworks/

#
# настроим пути поиска библиотек
#
# для quazip
#
install_name_tool -change /Users/macuser/Qt/5.3/clang_64/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ../Release/bin/Scenarist/Scenarist.app/Contents/Frameworks/libquazip.1.dylib 

#
# для rtf-qt
#
install_name_tool -change libquazip.1.dylib @executable_path/../Frameworks/libquazip.1.dylib ../Release/bin/Scenarist/Scenarist.app/Contents/Frameworks/librtf-qt.1.dylib 
install_name_tool -change /Users/macuser/Qt/5.3/clang_64/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ../Release/bin/Scenarist/Scenarist.app/Contents/Frameworks/librtf-qt.1.dylib 
install_name_tool -change /Users/macuser/Qt/5.3/clang_64/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui ../Release/bin/Scenarist/Scenarist.app/Contents/Frameworks/librtf-qt.1.dylib 

#
# скопируем app-файл в текущую папку
#
cp -R ../Release/bin/Scenarist/Scenarist.app ./Scenarist.app

# запустить скрипт создания dmg-файла
./make_dmg.sh -i ../../src/bin/Scenarist/logo.icns -b cover.png -c "462:252:176:258" -s "640:400"  Scenarist.app 

# удалить app-файл
rm -R ./Scenarist.app