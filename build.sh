#!/bin/bash

mkdir cmake-build-debug &&
  cd cmake-build-debug &&
  cmake .. && make all &&
  cd .. &&
  mkdir bin &&
  cp cmake-build-debug/DandyBotNative bin &&
  cp cmake-build-debug/sharedLib/libscript.so bin
