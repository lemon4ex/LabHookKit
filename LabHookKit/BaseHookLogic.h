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
    
    struct HookModifyInfo{
        bool isClassMethod; ///< 是否是类方法
        std::string methodName; ///< 方法名
        std::string typeEncoding; ///< 类型列表
        HookMagicFuncPtr methodIMP; ///< 方法实现
        int modifyType; ///< 0：Hook，1：新增方法
    };
    
    class BaseHookLogic {
        std::map<std::string,ClassHookInfo *> _hookInfoMap;
    public:
        ClassHookInfo *getClassHookInfo(SEL sel);
        bool hookInstanceMethod(const std::string &name, HookMagicFuncPtr imp); ///< 挂钩OC实例方法
        bool hookClassMethod(const std::string &name, HookMagicFuncPtr imp); ///< 挂钩OC类方法
        bool hookObjCMethod(Class _class, const std::string &name, HookMagicFuncPtr imp); ///< 挂钩OC方法
        bool addInstanceMethod(const std::string &name, HookMagicFuncPtr imp, const std::string &types);
        bool addClassMethod(const std::string &name, HookMagicFuncPtr imp, const std::string &types);
        bool addObjCMethod(Class _class,const std::string &name, HookMagicFuncPtr imp, const std::string &types);
        
    public:
        virtual ~BaseHookLogic();
        virtual void initHook() = 0;
        virtual std::string getClassName() = 0; ///< 被Hook的OC类名
        
    };
}
#endif
