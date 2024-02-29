#!/bin/bash
echo -e "<< File Handling >>"

echo -n "Testing file"
timeout 0.2s ./maze invalid_maze_empty.txt > tmp
if grep -q "Error opening file!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing bad data (format)  - "
timeout 0.2s ./maze invalid_maze_height.txt > tmp
if grep -q "Invalid maze! Rows have different lengths." tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing bad data (characters) - "
timeout 0.2s ./maze invalid_maze_char.txt > tmp
if grep -q "Invalid maze! Invalid character detected: %c" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "<< User Input Test >>"

echo -n "Testing move 'W' - "
echo "W" | timeout 0.2s ./maze valid_maze.txt > tmp
if grep -q "You moved up!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing move 'w' - "
echo "w" | timeout 0.2s ./maze valid_maze2.txt > tmp
if grep -q "You moved up!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing move 'A' - "
echo "A" | timeout 0.2s ./maze valid_maze3.txt > tmp
if grep -q "You moved left!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing move 'a' - "
echo "a" | timeout 0.2s ./maze valid_maze.txt > tmp
if grep -q "You moved left!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing move 'S' - "
echo "S" | timeout 0.2s ./maze valid_maze4.txt > tmp
if grep -q "You moved down!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing move 's' - "
echo "s" | timeout 0.2s ./maze valid_maze2.txt > tmp
if grep -q "You moved down!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing move 'D' - "
echo "D" | timeout 0.2s ./maze valid_maze3.txt > tmp
if grep -q "You moved right!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing move 'M' - "
echo "M" | timeout 0.2s ./maze valid_maze2.txt > tmp
if grep -q "This is you current location!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing move 'm' - "
echo "m" | timeout 0.2s ./maze valid_maze4.txt > tmp
if grep -q "This is you current location!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing move 'd' - "
echo "d" | timeout 0.2s ./maze valid_maze.txt > tmp
if grep -q "You moved right!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing invalid move 'z' - "
echo "z" | timeout 0.2s ./maze valid_maze3.txt > tmp
if grep -q "Invalid move!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


# Cleanup temporary files
rm tmp
