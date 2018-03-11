// Copyright 2018 Qi Yao

#ifndef MODULES_KRIS_MAYA_INCLUDE_KRIS_KRIS_MAYA_MULTITHREAD_SEPERATE_H_
#define MODULES_KRIS_MAYA_INCLUDE_KRIS_KRIS_MAYA_MULTITHREAD_SEPERATE_H_

WINDOWS_DISABLE_ALL_WARNING
#include "maya/MIOStream.h"
#include "maya/MPxCommand.h"

WINDOWS_ENABLE_ALL_WARNING

namespace kris
{
class Multithread_Seperate : public MPxCommand
{
 public:
  Multithread_Seperate();
  ~Multithread_Seperate() override;

  static void *creator();

  MStatus doIt(const MArgList &args) override;
};

}  // namespace kris

#endif  // MODULES_KRIS_MAYA_INCLUDE_KRIS_KRIS_MAYA_MULTITHREAD_SEPERATE_H_
