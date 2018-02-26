// Copyright 2018 Qi Yao

#include "Kris/Kris_Maya/Multithread_Seperate.h"

// #include <iostream>

WINDOWS_DISABLE_ALL_WARNING
// #include "opencv2/opencv.hpp"
WINDOWS_ENABLE_ALL_WARNING

namespace kris
{
Multithread_Seperate::Multithread_Seperate()
{
}

Multithread_Seperate::~Multithread_Seperate()
{
}

void *Multithread_Seperate::creator()
{
  return new Multithread_Seperate;
}

MStatus Multithread_Seperate::doIt(const MArgList &)
{
  cout << "Hello World\n" << endl;
  return MS::kSuccess;
}

}  // namespace kris
