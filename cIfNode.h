#pragma once
//*******************************************************
// Purpose: Class for an if statement
//
// Author: Philip Howard
// Email:  phil.howard@oit.edu
//
// Date: 2/20/2015
//
//*******************************************************

#include <string>

#include "cStmtNode.h"
#include "cExprNode.h"

class cIfNode : public cStmtNode
{
  public:
    cIfNode(cExprNode *expr, cStmtNode *ifPart, cStmtNode *elsePart) 
        : cStmtNode()
    {
        mExpr = expr;
        mStmt = ifPart;
        mElse = elsePart;
    }

    virtual std::string toString()
    {
        std::string result("(IF: ");
        result += mExpr->toString();
        result += "\n" + mStmt->toString();
        if (mElse != NULL) result += "\nELSE:\n" + mElse->toString();
        result += "\n)";
        return result;
    }

  protected:
    cExprNode *mExpr;       // conditional expression
    cStmtNode *mStmt;       // statements for if cond is true
    cStmtNode *mElse;       // optional statements for if cond is false
};

