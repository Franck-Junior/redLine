#!/bin/bash
 
getFiles() {
   Rep="$1"
   for item in $Rep/*
   do [ -f "$item" ] && echo "$item"
      [ -d "$item" ] && getFiles "$item"
   done
}
 
[ -d "${1:-.}" ] && getFiles ${1:-.}
