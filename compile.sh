export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH

#./main ; exit

g++ -o main main.cpp -I./include -L./lib -lraylib

if [ ! $? -eq 0 ]; then
    echo "exit error"; exit;
fi

./main