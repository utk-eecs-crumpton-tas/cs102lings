#!/bin/bash
if [ -f "student/$1/$1.cpp" ]; then
  echo "Project already exists! rm -rf the project if you wish to start fresh (there will be no recovery if you do this!)"
  exit 1;
fi
