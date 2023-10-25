#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Not specified <source_file> after $0"
	exit 1
fi

SOURCE_FILE="$1"
TEMP_DIR=$(mktemp -d)

exit_handler() {
	rm -rf "$TEMP_DIR"
}

trap exit_handler EXIT SIGHUP SIGINT SIGQUIT SIGPIPE SIGTERM

OUTPUT_FILE=$(grep -o "\&Output: [a-zA-Z0-9_]*\.out" "$SOURCE_FILE" | awk '{print $2}')

if [ -z "$OUTPUT_FILE" ]; then
	echo "Unspecified comment with the name of the output file as <\$Output: <output_filename>.out>"
        exit 2
fi

case "$SOURCE_FILE" in
	*.c)
	  gcc "$SOURCE_FILE" -o "$TEMP_DIR/$OUTPUT_FILE"
	  ;;
	*.cpp)
	  g++ "$SOURCE_FILE" -o "$TEMP_DIR/$OUTPUT_FILE"
	  ;;
	*.tex)
	  pdflatex -output-directory="$TEMP_DIR" "$SOURCE_FILE"
	  ;;
	*)
	  echo "Unsupported file type! Supported file types is .cpp/.c/.tex"
	  exit 3
esac

if [ $? -ne 0 ]; then
	echo "Compilation failed"
	exit 4
fi

mv "$TEMP_DIR/$OUTPUT_FILE" "$(dirname "$SOURCE_FILE")/$OUTPUT_FILE"

echo "Compilation succeeded. Output: $(dirname "$SOURCE_FILE")/$OUTPUT_FILE"
