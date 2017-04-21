#!/bin/bash

FILES=./data/images/jpg/*

for f in $FILES
do
	mv -- "$f" "${f/%.jpeg/.jpg}"
done
