#!/bin/bash

../script/listFile.sh $1 | wc -l >> ../script/listFile.txt
../script/listFile.sh $1 >> ../script/listFile.txt
