#pragma once
//*******************************************************
// Purpose: Base class for all AST nodes
//
// Author: Casey Schurman
// Email:  casey.schurman@oit.edu
//
// Date: 2/20/2015
//
//*******************************************************

#include <iostream>
#include <string>
#include "codegen.h"

class cAstNode
{
  public:
    cAstNode() {mSemanticError = false;}

    // return a string representation of the class
    virtual std::string toString() = 0;
    
    // recursively go through tree and children nodes and will compute size and
    // offset values
    virtual int ComputeOffsets(int base)
    {
        return base;
    }

    // return true if a semantic error was detected in this node
    virtual bool SemanticError() { return mSemanticError; }
    
    virtual void GenerateCode()
    {}

  protected:
    bool mSemanticError;        // true indicates this node has a semantic error
};

