#pragma once
//*******************************************************
// Purpose: Class for binary expressions
//
// Author: Casey Schurman
// Email:  casey.schurman@oit.edu
//
// Date: 3/3/2015
//
//*******************************************************

#include <string>

#include "cExprNode.h"

class cBinaryExprNode : public cExprNode
{
  public:
    cBinaryExprNode(cExprNode *left, char op, cExprNode *right) : cExprNode()
    {
        mLeftExpr = left;
        mOperator = op;
        mRightExpr = right;
    }

    // determine type based on types of operands
    // Normal promotion rules apply
    virtual cDeclNode *GetType()
    {
        cDeclNode *leftType  = mLeftExpr->GetType();
        cDeclNode *rightType = mRightExpr->GetType();
        cDeclNode *floatType = symbolTableRoot->Lookup("float")->GetType();
        cDeclNode *intType   = symbolTableRoot->Lookup("int")->GetType();

        if (leftType == rightType) return leftType;
        if (leftType->IsFloat() || rightType->IsFloat()) return floatType;
        return intType;
    }

    virtual std::string toString()
    {
        std::string result("(EXPR: ");
        result += mLeftExpr->toString() + " " 
               + mOperator + " " 
               + mRightExpr->toString();
        result += ")";

        return result;
    }
    
    virtual int ComputeOffsets(int base)
    {
        mLeftExpr->ComputeOffsets(base);

        mRightExpr->ComputeOffsets(base);
        
        return base;
    }

  protected:
    cExprNode *mLeftExpr;       // left expression
    cExprNode *mRightExpr;      // right expression
    char mOperator;             // operator: '+', '-', '*', '/', '%'
};

