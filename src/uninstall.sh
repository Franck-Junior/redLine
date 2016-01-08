#!/usr/bin/env


echo "\nAre you sure you want to uninstall Upssearchtech ? (y)/any key"
echo "\nEtes-vous sur de vouloir désinstaller Upssearchtech ? (y)/any key"

read choice

if [ "$choice" -eq "y"]; then
  echo "\nSad to see you go..."
  echo "\nAu revoir..."
  rm -rf .
  exit 0
else
  echo "\nYou made the right choice ! You will not be disappointed !"
  echo "\nMerci de rester avec nous ! Vous ne le regretterez pas !"
  exit 1
fi
