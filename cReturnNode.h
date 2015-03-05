#pragma once
//*******************************************************
// Purpose: Class for a return statement
//
// Author: Casey Schurman
// Email:  casey.schurman@oit.edu
//
// Date: 3/3/2015
//
//*******************************************************

#include <string>

#include "cStmtNode.h"
#include "cExprNode.h"

class cReturnNode : public cStmtNode
{
  public:
    cReturnNode(cExprNode *expr) : cStmtNode()
    {
        mExpr = expr;
    }

    virtual std::string toString()
    {
        std::string result("RETURN: ");
        result += mExpr->toString();
        return result;
    }
    
    virtual int ComputeOffsets(int base)
    {
        mExpr->ComputeOffsets(base);
        
        return base;
    }

  protected:
    cExprNode *mExpr;       // value to be returned
};

