// Copyright 2018 Qi Yao
WINDOWS_DISABLE_ALL_WARNING
#include "maya/MFnPlugin.h"
WINDOWS_ENABLE_ALL_WARNING
#include "Kris/Kris_Maya/Multithread_Seperate.h"

MStatus initializePlugin(MObject obj)
{
  MFnPlugin plugin(obj, "Qi Yao", "0.0.0.1", "2018");

  MStatus status = plugin.registerCommand("Multithread_Seperate",
                                          kris::Multithread_Seperate::creator);
  CHECK_MSTATUS_AND_RETURN_IT(status);
  return status;
}

MStatus uninitializePlugin(MObject obj)
{
  MFnPlugin plugin(obj);
  MStatus status = plugin.deregisterCommand("Multithread_Seperate");
  CHECK_MSTATUS_AND_RETURN_IT(status);
  return status;
}
