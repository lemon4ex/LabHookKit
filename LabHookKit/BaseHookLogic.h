//
//  BaseHookLogic.h
//  TaiChi
//
//  Created by lemon4ex on 2018/3/8.
//  Copyright © 2018年 lemon4ex. All rights reserved.
//
#ifndef BaseHookLogic_h
#define BaseHookLogic_h

#include <map>
#include <string>
#include <objc/runtime.h>

namespace LabHookKit {
    
    class BaseHookLogic;
    
    typedef void (BaseHookLogic::*HookMagicFuncPtr)(SEL sel, ...);
    
    struct ClassHookInfo {
        std::string className;
        std::string methodName;
        IMP originImp;
    };
    
    class BaseHookLogic {
        std::string _className;
        std::map<std::string,ClassHookInfo *> _hookInfoMap;
    public:
        BaseHookLogic(const std::string &className);
        std::string getClassName();
        virtual ~BaseHookLogic();
//        void setAssociatedObject(id object, const void *key, id value, objc_AssociationPolicy policy);
//        id getAssociatedObject(id object, const void *key);
        ClassHookInfo *getClassHookInfo(SEL sel);
        bool hookInstanceMethod(const std::string &name, HookMagicFuncPtr imp); ///< 挂钩OC实例方法
        bool hookClassMethod(const std::string &name, HookMagicFuncPtr imp); ///< 挂钩OC类方法
        bool hookObjCMethod(Class _class, const std::string &name, HookMagicFuncPtr imp); ///< 挂钩OC方法
        bool addInstanceMethod(const std::string &name, HookMagicFuncPtr imp, const std::string &types);
        bool addClassMethod(const std::string &name, HookMagicFuncPtr imp, const std::string &types);
        bool addObjCMethod(Class _class,const std::string &name, HookMagicFuncPtr imp, const std::string &types);
    public:
        virtual void initHook() = 0;
        
    };
}
#endif
