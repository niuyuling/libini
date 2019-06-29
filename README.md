# libini
    非常小的读取、写入ini配置文件c库.
    支持字符串、整形、长整型、浮点型.
    注释是"//"、"#"、";".
    会读取等号右边所有字符.
    支持等号左右有若干空格.
    
# build
    git clone https://github.com/niuyuling/libini
    cd libini
    make

# test
    gcc -Wall test.c -o test -L./ -lini -static
    ./test