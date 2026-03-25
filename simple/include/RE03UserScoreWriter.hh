/// \file runAndEvent/RE03/include/RE03UserScoreWriter.hh
/// \brief Definition of the RE03UserScoreWriter class
//
//

#ifndef RE03UserScoreWriter_h
#define RE03UserScoreWriter_h 1

#include "G4VScoreWriter.hh"
#include "globals.hh"

// class description:
//
//  This class represents storing the scored quantity into a file.
//

class RE03UserScoreWriter : public G4VScoreWriter
{
  public:
    RE03UserScoreWriter();
    virtual ~RE03UserScoreWriter();

  public:
    // store a quantity into a file
    virtual void DumpQuantityToFile(const G4String& psName, const G4String& fileName,
                                    const G4String& option);
};

#endif
