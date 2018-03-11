// Copyright 2018 Qi Yao

#include "Kris/Kris_Maya/Multithread_Seperate.h"

WINDOWS_DISABLE_ALL_WARNING
#include <math.h>

#include "maya/MArgList.h"
#include "maya/MDoubleArray.h"
#include "maya/MFnNurbsCurve.h"
#include "maya/MIOStream.h"
#include "maya/MPoint.h"
#include "maya/MPointArray.h"
#include "maya/MSimple.h"
WINDOWS_ENABLE_ALL_WARNING

namespace kris
{
Multithread_Seperate::Multithread_Seperate()
{
}

Multithread_Seperate::~Multithread_Seperate()
{
}

void* Multithread_Seperate::creator()
{
  return new Multithread_Seperate;
}

MStatus Multithread_Seperate::doIt(const MArgList& args)
{
  MStatus stat;
  const unsigned deg    = 3;                    // Curve Degree
  const unsigned ncvs   = 20;                   // Number of CVs
  const unsigned spans  = ncvs - deg;           // Number of spans
  const unsigned nknots = spans + 2 * deg - 1;  // Number of knots
  double radius         = 4.0;                  // Helix radius
  double pitch          = 0.5;                  // Helix pitch
  unsigned int i;
  // Parse the arguments.
  for (i = 0; i < args.length(); i++)
  {
    if (MString("-p") == args.asString(i, &stat) && MS::kSuccess == stat)
    {
      double tmp = args.asDouble(++i, &stat);
      if (MS::kSuccess == stat)
      {
        pitch = tmp;
      }
    }
    else if (MString("-r") == args.asString(i, &stat) && MS::kSuccess == stat)
    {
      double tmp = args.asDouble(++i, &stat);
      if (MS::kSuccess == stat)
      {
        radius = tmp;
      }
    }
  }
  MPointArray controlVertices;
  MDoubleArray knotSequences;
  // Set up cvs and knots for the helix
  //
  for (i = 0; i < ncvs; i++)
  {
    controlVertices.append(MPoint(radius * cos(static_cast<double>(i)),
                                  pitch * static_cast<double>(i),
                                  radius * sin(static_cast<double>(i))));
  }
  for (i = 0; i < nknots; i++)
  {
    knotSequences.append(static_cast<double>(i));
  }
  // Now create the curve
  //
  MFnNurbsCurve curveFn;
  MObject curve = curveFn.create(controlVertices,
                                 knotSequences,
                                 deg,
                                 MFnNurbsCurve::kOpen,
                                 false,
                                 false,
                                 MObject::kNullObj,
                                 &stat);
  if (MS::kSuccess != stat)
  {
    cout << "Error creating curve.\n";
  }
  return stat;
}

}  // namespace kris
