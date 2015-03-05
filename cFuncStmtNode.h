#pragma once
//*******************************************************
// Purpose: Class for a function call as a statement
//
// Author: Philip Howard
// Email:  phil.howard@oit.edu
//
// Date: 2/20/2015
//
//*******************************************************

#include <string>

#include "cStmtNode.h"

class cFuncStmtNode : public cStmtNode
{
  public:
    cFuncStmtNode(cFuncCallNode *call) : cStmtNode()
    {
        mCall = call;
    }

    virtual std::string toString()
    {
        return mCall->toString();
    }

  protected:
    cFuncCallNode *mCall;
};

