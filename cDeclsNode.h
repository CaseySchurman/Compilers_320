#pragma once
//*******************************************************
// Purpose: Base class for all declarations
//
// Author: Casey Schurman
// Email:  casey.schurman@oit.edu
//
// Date: 2/20/2015
//
//*******************************************************

#include <string>
#include <list>
using std::list;

#include "cAstNode.h"
#include "cAstList.h"
#include "cDeclNode.h"

using std::list;

class cDeclsNode : public cAstNode
{
  public:
    // constructor places first decl in list
    cDeclsNode(cDeclNode *decl) : cAstNode()
    {
        mList = new list<cDeclNode *>();
        mList->push_back(decl);
        
        mSize = -1;
    }
    
    int Size()
    {
      return mSize;
    }
      
    virtual int ComputeOffsets(int base)
    {
        int offset = base;
      
        list<cDeclNode *>::iterator it = mList->begin();
      
        for(;it != mList->end(); it++)
        {
            offset = (*it)->ComputeOffsets(offset);
        }
        
        mSize = offset - base;
        
        return offset;
    }

    // add a declaration to the list
    void AddNode(cDeclNode *decl) 
    {
        mList->push_back(decl);
    }

    virtual std::string toString()
    {
        std::string result("DECLS:\n{\n");
        result += ListToString<cDeclNode *>(mList, true);
        result += "}\n";

        return result;
    }
    
    virtual void GenerateCode()
    {
        list<cDeclNode *>::iterator it = mList->begin();
      
        for(;it != mList->end(); it++)
        {
            (*it)->GenerateCode();
        }
    }

  protected:
    list<cDeclNode *> *mList;       // list of delcarations
    int mSize;
};

