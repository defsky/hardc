echo "Running unit tests..."

# LD_LIBRARY_PATH=build/

for i in tests/*_tests
do
    if test -f $i
    then
        if $VALGRIND ./$i 2>>tests/tests.log
        then
            echo "-----------------------------"
            echo -e "\033[32m$i PASS\033[0m"
            echo "-----------------------------"
        else
            echo "-----------------------------"
            echo -e "\033[31mERROR in test $i: here's tests/tests.log\033[0m"
            echo "-----------------------------"
            tail tests/tests.log
            exit 1
        fi
    fi
done

echo ""
