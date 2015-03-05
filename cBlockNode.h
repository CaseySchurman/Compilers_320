#pragma once
//*******************************************************
// Purpose: Class to represent a block
//
// Author: Casey Schurman
// Email:  casey.schurman@oit.edu
//
// Date: 2/20/2015
//
//*******************************************************

#include <string>

#include "cStmtNode.h"
#include "cStmtsNode.h"
#include "cDeclsNode.h"
#include <string>
using std::to_string;

// blocks can be statements (e.g. if (cond) {block}
class cBlockNode : public cStmtNode
{
  public:
    cBlockNode(cDeclsNode *decls, cStmtsNode *stmts) : cStmtNode()
    {
        mDecls = decls;
        mStmts = stmts;
        
        mSize = -1;
    }
    
    virtual std::string toString()
    {
        std::string result("BLOCK: ");
    
        if (mSize != -1)
        {
            result += "size: " + to_string(mSize) + "\n{\n";
        }
        if (mDecls != NULL) 
        { 
            result += mDecls->toString();
        }
        if (mStmts != NULL)
        {
            result += mStmts->toString();
        }
        
        
        return  result + "}\n";
    }
    
    int ComputeOffsets(int base)
    {
        int offset = base;
        
        if (mDecls != nullptr)
        {
            offset = mDecls->ComputeOffsets(offset);
        }
        
        if (mStmts != nullptr)
        {
            offset = mStmts->ComputeOffsets(offset);
        }
        
        mSize = offset - base;
        
        
        return base;
    }

  protected:
    cDeclsNode *mDecls;     // declarations
    cStmtsNode *mStmts;     // statements
    int mSize;
};

