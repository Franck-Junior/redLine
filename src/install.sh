#!/usr/bin/env

if $# != 1; then
echo "\nProper syntax/Syntaxe correcte : "
echo "\n ./install.sh \"path\""
exit 1
fi

echo "\nThis script will install Upssearchtech"
echo "\nCe script installera Upssearchtech"
echo "\nCopying files...\nCopie de fichiers..."
mkdir -p $1

mv upssearchtech $1

if [$? -eq 0]
then
    echo "\nUpssearchtech has been succesfuly installed !"
    echo "\nInstallation d'Upssearchtech réussie !"
    exit 0
else
    echo "\nThe installation failed, maybe you don't have sufficient rights ?"
    echo "\nL'installation a échouée, peut-être qu'il vous manque des droits ?"
    exit 2
fi
