echo // this file is generated by empty.sh, do not edit > emptyconts.cpp
echo \#include \"mainwindow.hpp\" >> emptyconts.cpp
echo const char MainWindow::m_acEmptyConts[] = { >> emptyconts.cpp
hexdump -ve '16/1 "(char)0x0%x, " "\n"' empty.pdf >> emptyconts.cpp
echo 0x00 }\; >> emptyconts.cpp

