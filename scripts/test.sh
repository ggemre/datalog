#!/bin/sh

# Set the path to C++ executable
mkdir -p debug
g++ -Wall -Werror -std=c++17 -g src/*.cpp -o debug/test
EXECUTABLE="./debug/test"

# Iterate over each input file in the tests/ directory
for input_file in tests/*/*.txt; do
    if [[ "${input_file}" == *"input"* ]]; then
        # Extract the directory and file name without extension
        dir=$(dirname "${input_file}")
        file=$(basename "${input_file}" .txt)

        # Extract the number from the input file name
        num=$(echo "${file}" | sed 's/input\([0-9]*\)/\1/')

        # Form the corresponding answer file name
        answer_file="${dir}/answer${num}.txt"

        # Run the executable with the current input file and capture its output
        output=$("${EXECUTABLE}" "${input_file}")

        # Read the content of the answer file
        expected_output=$(<"${answer_file}")

        # Compare the output of the executable with the expected output
        if [ "${output}" == "${expected_output}" ]; then
            echo "Test ${dir}/${file}: PASSED"
        else
            echo "Test ${dir}/${file}: FAILED"
        fi
    fi
done
