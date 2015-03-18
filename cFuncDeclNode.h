#pragma once
//*******************************************************
// Purpose: Class for a function definiiton or delcaration
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
#include "cExprNode.h"
#include "cParamsSpecNode.h"

class cFuncDeclNode : public cDeclNode
{
  public:
    // return type and name of function
    cFuncDeclNode(cSymbol *type, cSymbol *id)
    {
        cSymbol *existingSymbol = symbolTableRoot->LocalLookup(id->Name());
        if (existingSymbol != NULL && existingSymbol->GetType()->IsFunc())
        {
            // we already have a declaration, so make this one match
            cFuncDeclNode *fDecl = 
                dynamic_cast<cFuncDeclNode *>(existingSymbol->GetType());
            mId = existingSymbol;
            mReturnType = fDecl->mReturnType;
            mParams = fDecl->mParams;
            mDecls = fDecl->mDecls;
            mStmts = fDecl->mStmts;
            mParamsSet = fDecl->mParamsSet;
            mId->SetType(this);
        } 
        else 
        {
            symbolTableRoot->Insert(id);
            mReturnType = type;
            mId = id;
            mParams = NULL;
            mDecls = NULL;
            mStmts = NULL;
            mParamsSet = false;
            mId->SetType(this);
        }
    }

    // return the type of the return value
    virtual cDeclNode *GetBaseType()
    {
        return mReturnType->GetType();
    }

    virtual bool IsFunc()   { return true; }

    // size of the returned value
    virtual int ReturnSize(){ return mReturnType->GetType()->Size(); }

    // set the params. This can't be done in the constructor because
    // we create the node on the function header
    void SetParams(cParamsSpecNode *params)
    {
        if (!mParamsSet)
        {
            mParams = params;
            mParamsSet = true;
        }
    }

    // return the parameter list
    cParamsSpecNode *GetParams()
    { return mParams; }

    // set the local var delcs and the statments
    void SetBody(cDeclsNode *decls, cStmtsNode *stmts)
    {
        mDecls = decls;
        mStmts = stmts;
    }

    virtual std::string toString()
    {
        std::string result("(FUNC: ");
        result += mId->toString();
        if (mParams != NULL) 
            result += mParams->toString();
        else
            result += "()";
        if (mDecls != NULL) result += "\n" + mDecls->toString();
        if (mStmts != NULL) result += "\n" + mStmts->toString();
        //if (mDeclsSize != 0) result += "\nsize: " + std::to_string(mDeclsSize);
        result += "\nsize: " + std::to_string(mSize);
        result += "\n)";
        return result;
    }
    
    int ComputeOffsets(int base)
    {
        int offset = 0;
        
        if (mParams != nullptr)
        {
            offset = mParams->ComputeOffsets(offset);
        }
        
        if (mDecls != nullptr)
        {
            offset = mDecls->ComputeOffsets(offset);
        }
        
        if (mStmts != nullptr)
        {
            offset = mStmts->ComputeOffsets(offset);
        }
        
        if (mDecls != nullptr)
        {
            mSize = mDecls->Size();
        }
        
        return base;
    }
    void GenerateCode()
    {
        //Tried doing this, didn't work
        /*StartFunctionOutput();
        EmitString(mReturnType->Name() + '_' + std::to_string(mReturnType->GetSequence()) + "(");
            
        if (mParams != nullptr)
            mParams->GenerateCode();
            
        EmitString(")\n{\n");
                
        if (mDecls != nullptr)
            EmitString("Stack_Pointer += " + std::to_string(mSize) + ";\n");
                
        if (mStmts != nullptr)
            mStmts->GenerateCode();
            
        EmitString("Stack_Pointer = Frame_Pointer;\n");
        EmitString("Stack_Pointer -= 4;\n");
        EmitString("Frame_Pointer = (*(int *)(&Memory[(Stack_Pointer)]));\n");
        
        EmitString("}\n");
        EndFunctionOutput();*/
        
        
        //Ended up doing this
        EmitString("int ");
        EmitString(mId->Name());
        EmitString("( ");
        
        if(mParams != nullptr)
        {
            mParams->GenerateCode();
        }
        EmitString(" )\n{\n");
        
        if(mDecls != nullptr)
        {
            mDecls->GenerateCode();
        }
        
        if(mStmts != nullptr)
        {
            mStmts->GenerateCode();
        }
        
        EmitString("\n}\n");
    }

  protected:
    cSymbol *mReturnType;       // return type of function
    cParamsSpecNode *mParams;   // formal parameter list
    cDeclsNode *mDecls;         // local variables
    cStmtsNode *mStmts;         // executable statements
    bool mParamsSet;            // indicates parameters have been set
    int mDeclsSize;             // size of the declarations. Needed to
                                // allocate space on the stack for locals
};

