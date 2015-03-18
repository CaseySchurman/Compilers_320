#pragma once
//*******************************************************
// Purpose: Class for a variable reference. 
//
// Author: Casey Schurman
// Email:  casey.schurman@oit.edu
//
// Date: 3/1/2015
//
//*******************************************************

#include <string>
#include <list>
using std::list;

#include "cAstNode.h"
#include "cExprNode.h"
#include "cAstList.h"
#include "cStructDeclNode.h"
#include "cArrayValNode.h"
#include "cVarDeclNode.h"
#include "cSymbolTable.h"
#include "cVarPartNode.h"

#include "parse.h"

class cVarRefNode : public cExprNode
{
  public:
    cVarRefNode(cVarPartNode *var) 
    {
        cDeclNode *baseDecl;

        if (symbolTableRoot->Lookup(var->Name()) == NULL)
        {
            semantic_error("Symbol " + var->Name() + " not defined");
            mSemanticError = true;
        } 
        else
        {
            mName = var->Name();
            mList = new list<cVarPartNode *>();
            mList->push_back(var);
            baseDecl = var->GetDecl();
            if (!baseDecl->IsArray())
                baseDecl = baseDecl->GetBaseType();
            if (baseDecl->IsArray() && var->IsArrayRef())
                baseDecl = baseDecl->GetBaseType();
            mDepthDecl = baseDecl;
        }
        
        mSize = -1;
        mOffset = -1;
    }

    void AddNode(cVarPartNode *field) 
    {
        if (!mDepthDecl->IsStruct())
        {
            semantic_error(mName + " is not a struct");
            mSemanticError = true;
        } else {
            cStructDeclNode *base = dynamic_cast<cStructDeclNode *>(mDepthDecl);
            cSymbol *sField = base->Lookup(field->Name());
            if (sField == NULL)
            {
                semantic_error(field->Name() + " is not a field of " + mName);
                mSemanticError = true;
            } else {
                mDepthDecl = sField->GetType();
                field->SetField(mDepthDecl);
                if (!mDepthDecl->IsArray())
                    mDepthDecl = mDepthDecl->GetBaseType();
                if (mDepthDecl->IsArray() && field->IsArrayRef())
                    mDepthDecl = mDepthDecl->GetBaseType();
                mList->push_back(field);
                field->UpdateSymbol(sField);
                field->SetDecl(base);

                mName += "." + field->Name();
            }
        }
    }

    virtual cDeclNode *GetType()
    {
        return mDepthDecl;
    }

    std::string Name() { return mName; }

    virtual std::string toString()
    {
        std::string result;
        if (mList != NULL) result += ListToString(mList, false);
        // Note: change in class heirarchy forces the ')' 
        // to be appended here insead of inside cVarPartNode.
        for (unsigned int ii=0; ii<mList->size() - 1; ii++)
        {
            result += ")";
        }
        result += "size: " + to_string(mSize) + " offset: " + to_string(mOffset);
        result += ")";

        return result;
    }
    
    virtual int ComputeOffsets(int base)
    {
        list<cVarPartNode *>::iterator it = mList->begin();
        mOffset = (*it)->GetDecl()->GetOffset();
      
        for(it++; it != mList->end(); it++)
        {
            mOffset += (*it)->GetFieldDeclOffsets();
        }
        
        if(mDepthDecl->IsArray())
        {
            mSize = mDepthDecl->GetBaseType()->Size();
        }
        else
        {
            mSize = mDepthDecl->Size();
        }
        
        return base;
    }
    
    void GenerateCode()
    {
        if(mList->back()->GetDecl()->IsFloat())
        {
            EmitString("(*(double *)(&Memory[(Frame_Pointer + " + std::to_string(mOffset) + ")]))");
        }
        else if(mList->back()->GetDecl()->IsInt())
        {
            EmitString("(*(int *)(&Memory[(Frame_Pointer + " + std::to_string(mOffset) + ")]))");
        }
    }

  protected:
    std::string mName;
    list<cVarPartNode *> *mList;
    cDeclNode *mDepthDecl;
    int mSize;
    int mOffset;
};
