#pragma once
//*******************************************************
// Purpose: A list of actual params passed to a function
//
// Author: Casey Schurman
// Email:  casey.schurman@oit.edu
//
// Date: 3/1/2015
//
//*******************************************************

#include <string>
#include <list>

#include "cAstNode.h"
#include "cExprNode.h"
#include "cAstList.h"

using std::list;

class cParamNode: public cAstNode
{
  public:
    // place the first param in the list
    cParamNode(cExprNode *param) : cAstNode()
    {
        mList = new list<cExprNode *>();
        if (param != NULL) mList->push_back(param);
    }

    // place the next param in the list
    void AddNode(cExprNode *param) 
    {
        mList->push_back(param);
    }

    // return a specific param
    cExprNode *GetParam(int index)
    {
        return ListGetItem(mList, index);
    }

    int NumParams()
    { return mList->size(); }

    virtual std::string toString()
    {
        std::string result("(PARAM:");
        result += ListToString(mList, false);
        result += ")\n";

        return result;
    }
    
    int ComputeOffsets(int base)
    {
        list<cExprNode *>::iterator it = mList->begin();
      
        for(;it != mList->end(); it++)
        {
            (*it)->ComputeOffsets(base);
        }
        
        return base;
    }

  protected:
    list<cExprNode *> *mList;       // list of parameters
};

