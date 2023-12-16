#!/bin/bash -e

if [ ! -e "/shared_volume/lock/lock_file.lock" ]; then
  echo > "/shared_volume/lock/lock_file.lock"
fi

shared_dir="/shared_volume"
lock_file="/shared_volume/lock/lock_file.lock"

generate_container_id() {
  echo $(date +%s%N | sha256sum | head -c 8)
}

find_first_available_filename() {
  local index=1
  while true; do
    filename=$(printf "%03d" $index)
    if [ ! -f "$shared_dir/$filename" ]; then
      break
    fi
    ((index++))
  done
}

create_file() {
  exec {fd}>$lock_file
  flock -s "$fd"

  find_first_available_filename

  digits=$(echo "$filename" | grep -oE '[0-9]+')
  index=$(echo "$digits" | sed 's/^0*//')

  text="$container_id $index"
  echo "$text" > "$shared_dir/$filename"

  flock -u "$fd"
}

delete_file() {
  if [ -f "$shared_dir/$filename" ]; then
    text=$(<"$shared_dir/$filename")

    rm -f "$shared_dir/$filename"

    echo "Container with id: $container_id deleted file: $filename that had text: $text"
  fi
}


container_id=$(generate_container_id)
while true; do

  create_file

  sleep 1

  delete_file

done
