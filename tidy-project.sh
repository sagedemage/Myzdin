#!/bin/bash

tidy_path="clang-tooling"

Help() {
    echo "-h    help"
    echo "-c    recompile the project"
    echo "-r    remove the $tidy_path directory"
    echo "-s    setup the $tidy_path directory"
    echo "-t    tidy the project"
}

while getopts ":chrst" arg; do
    
    case $arg in
        h) 
            Help
            exit;;
        c)
            cd $tidy_path
            meson compile
            exit;;
        r)
            rm -rf $tidy_path
            exit;;
        s)
            CC=clang meson $tidy_path
            cd $tidy_path
            meson compile
            exit;;
        t)
            cd $tidy_path
            meson compile tidy
            exit;;
        \?)
            echo "Invalid option: pass -h for help"
            exit;;
    esac
done

if [ $OPTIND -eq 1 ]
then 
    echo "No arguments passed: pass -h for help"
fi
