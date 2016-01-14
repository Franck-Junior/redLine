#!/bin/bash
type= file -bi $1 | cut -d = -f 2;
echo $type;
echo $1;
iconv -f $type -t UTF-8 $1 > $1;
