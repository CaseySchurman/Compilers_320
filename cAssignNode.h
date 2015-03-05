#pragma once
//*******************************************************
// Purpose: Class for an assignment statement
//
// Author: Casey Schurman
// Email:  casey.schurman@oit.edu
//
// Date: 2/20/2015
//
//*******************************************************

#include <string>

#include "cStmtNode.h"
#include "cExprNode.h"
#include "parse.h"

class cAssignNode : public cStmtNode
{
  public:
    cAssignNode(cVarRefNode *lval, cExprNode *expr) : cStmtNode()
    {
        mLval = lval;
        mExpr = expr;
        if (!lval->GetType()->CompatibleWith(expr->GetType()))
        {
            semantic_error("Cannot assign " + 
                    expr->GetType()->GetBaseType()->Name() +
                    " to " + lval->GetType()->GetBaseType()->Name());
        }
    }

    virtual std::string toString()
    {
        std::string result("(ASSIGN: ");
        result += mLval->toString();
        result += " = ";
        result += mExpr->toString();
        result += ")";
        return result;
    }
    
    int ComputeOffsets(int base)
    {
      if(mLval != nullptr)
      {
          mLval->ComputeOffsets(base);
      }
      
      if(mExpr != nullptr)
      {
          mExpr->ComputeOffsets(base);
      }
      
      return base;
    }

  protected:
    cExprNode *mExpr;       // the rhs of the assignment
    cVarRefNode *mLval;     // the lhs of the assignment`
};

