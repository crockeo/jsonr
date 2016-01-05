#!/bin/bash

# Name  : uninstall.sh
# Author: Cerek Hillen
#
# Description:
#   Reads from the install_manifest.txt created by CMake when 'make install'ing
#   the project to remove every installed file.

if [ -f install_manifest.txt ]; then
    while read p; do
        if [ -f "$p" ]; then
            if [ "$1" = "verbose" ]; then
                echo "Removing: $p"
            fi

            rm $p
        fi
    done < install_manifest.txt
else
    echo "Err: No install_manifest.txt exists."
fi
