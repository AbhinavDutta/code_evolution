#!/bin/bash
index_v=1
for commit in $(git log --pretty=format:%h "$1")
do
  padindex=$(printf %03d "$index_v")
  out="temp/$1.$padindex.$commit"
  echo "saving version $index_v to file $out for commit $commit"
  git show "$commit:./$1" > "$out"
  index_v=$((index_v+1))
  echo -n "$index_v"

done
