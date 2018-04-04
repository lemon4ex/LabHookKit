//
//  BaseImplementLogic.h
//  LabHookKit
//
//  Created by lemon4ex on 2018/3/12.
//  Copyright © 2018年 lemon4ex. All rights reserved.
//

#ifndef BaseImplementLogic_h
#define BaseImplementLogic_h

#include <map>
#include <string>
#include <objc/runtime.h>

namespace LabHookKit {
    class BaseImplementLogic;
    
    typedef void (BaseImplementLogic::*IMPMagicFuncPtr)(SEL sel, ...);
    
    class BaseImplementLogic {
        std::string _className;
        std::string _superClass;
        Class _class;
    public:
        BaseImplementLogic(const std::string &superClass, const std::string &className);
        std::string getClassName();
        void allocateClass();
        void registerClass();
        bool addInstanceMethod(const std::string &name, IMPMagicFuncPtr imp, const std::string &types);
        bool addClassMethod(const std::string &name, IMPMagicFuncPtr imp, const std::string &types);
        bool addObjCMethod(Class _class,const std::string &name, IMPMagicFuncPtr imp, const std::string &types);
//        bool addInstanceVar(const std::string &name, const std::string &types);
        virtual ~BaseImplementLogic();
        
        ///< 给类增加方法、属性等都在此函数中实现
        virtual void initImplement() = 0;
    };
}

#endif

