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
    
    struct ImplementInfo{
        bool isClassMethod; ///< 是否是类方法
        std::string methodName; ///< 方法名
        std::string typeEncoding; ///< 类型列表
        IMPMagicFuncPtr methodIMP; ///< 方法实现
    };
    
    class BaseImplementLogic {

        Class _class;
    public:
        void allocateClass();
        void registerClass();
        bool addInstanceMethod(const std::string &name, IMPMagicFuncPtr imp, const std::string &types);
        bool addClassMethod(const std::string &name, IMPMagicFuncPtr imp, const std::string &types);
        bool addObjCMethod(Class _class,const std::string &name, IMPMagicFuncPtr imp, const std::string &types);
        Class getClass();
    public:
        virtual ~BaseImplementLogic();
        virtual std::string getClassName() = 0;
        virtual std::string getSuperClassName() = 0;
        virtual void initImplement() = 0;
        
    };
}

#endif

