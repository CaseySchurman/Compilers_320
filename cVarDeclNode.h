#pragma once
//*******************************************************
// Purpose: Class for a variable declaration
//
// Author: Casey Schurman
// Email:  casey.schurman@oit.edu
//
// Date: 3/1/2015
//
//*******************************************************

#include <string>

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cStructDeclNode.h"
#include "cSymbol.h"
#include "parse.h"
#include <string>
using std::to_string;

class cVarDeclNode : public cDeclNode
{
  public:
    cVarDeclNode(cSymbol *type, cSymbol *id) : cDeclNode()
    {
        cSymbol *localId = symbolTableRoot->LocalLookup(id->Name());
        if (localId != NULL)
        {
            semantic_error("Symbol " + id->Name() +
                    " already defined in current scope");
        }
        // We may have an id from an outter scope. This will either
        // create a new symbol or return the already existing symbol
        // in the current scope.
        id = symbolTableRoot->Insert(id);

        mType = type->GetType();
        mId = id;
        mId->SetType(this);
        
        mOffset = -1;
    }

    // return the decl of the type
    virtual cDeclNode *GetBaseType()
    {
        return mType;
    }

    virtual bool IsArray()  { return mType->IsArray(); }
    virtual bool IsStruct() { return mType->IsStruct(); }
    virtual bool IsFloat()  { return mType->IsFloat(); }
    virtual bool IsInt()    { return mType->IsInt(); }
    
    virtual int ComputeOffsets(int base)
    {
        int ReturnVal = 0;
        
        if (mType->Size() >= WORD_SIZE)
        {
            //word aligns the data
            if(base % WORD_SIZE != 0)
            {
                base = (base + WORD_SIZE) / WORD_SIZE;
                base *= WORD_SIZE;
            }
        }
        
        mOffset = base;
        mSize = mType->Size();
        ReturnVal = mOffset + mSize;
        
        return ReturnVal;
    }

    virtual std::string toString()
    {
        std::string result("");
        result += mType->TypeId();
        result += " " + mId->toString();
        
        if (mSize != -1)
        {
            result += " size: " + to_string(mSize);
        }
        
        if (mOffset != -1)
        {
            result +=  " offset: " + to_string(mOffset);
        }
        
        return "VAR: " + result;
    }
    
    //virtual int GetOffset() { return mOffset; }

  protected:
    cDeclNode *mType;   // the type for the decl
                        // NOTE: this class inherits members from cDeclNode
};

