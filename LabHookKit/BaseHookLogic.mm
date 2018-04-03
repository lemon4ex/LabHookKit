//
//  BaseHookLogic.m
//  TaiChi
//
//  Created by lemon4ex on 2018/3/8.
//  Copyright © 2018年 lemon4ex. All rights reserved.
//

#import "BaseHookLogic.h"

namespace LabHookKit {
    
    BaseHookLogic::BaseHookLogic(const std::string &className):_className(className)
    {
        
    }
    
    BaseHookLogic::~BaseHookLogic()
    {
        
    }
    
    void BaseHookLogic::setAssociatedObject(id object, const void *key, id value, objc_AssociationPolicy policy)
    {
        objc_setAssociatedObject(object, key, value, policy);
    }
    
    id BaseHookLogic::getAssociatedObject(id object, const void *key)
    {
        return objc_getAssociatedObject(object, key);
    }
    
    bool BaseHookLogic::hookInstanceMethod(const std::string &name, HookMagicFuncPtr imp)
    {
        Class _class = objc_getClass(_className.c_str());
        return hookObjCMethod(_class, name, imp);
    }
    
    bool BaseHookLogic::hookClassMethod(const std::string &name, HookMagicFuncPtr imp)
    {
        Class _class = object_getClass(objc_getClass(_className.c_str()));
        return hookObjCMethod(_class, name, imp);
    }
    
    bool BaseHookLogic::hookObjCMethod(Class _class, const std::string &name, HookMagicFuncPtr imp)
    {
        SEL sel = sel_getUid(name.c_str());
        Method originalMethod = class_getInstanceMethod(_class, sel);
        if (!originalMethod) {
            return false;
        }
        
        void *function = &imp;
        if ((IMP)(*(size_t *)function) == method_getImplementation(originalMethod)) {
            return true;
        }
        
        IMP originImp = class_replaceMethod(_class, sel, (IMP)function, method_getTypeEncoding(originalMethod));
        if (!originImp) {
            originImp = method_getImplementation(originalMethod);
        }
        if (!originImp) {
            return false;
        }
        ClassHookInfo *hookInfo = new ClassHookInfo();
        hookInfo->className = _className;
        hookInfo->methodName = name;
        hookInfo->originImp = originImp;
        _hookInfoMap.insert(std::pair<std::string, ClassHookInfo *>(name,hookInfo));
        return true;
    }
    
    std::string BaseHookLogic::getClassName()
    {
        return _className;
    }
    
    ClassHookInfo *BaseHookLogic::getClassHookInfo(SEL sel)
    {
        std::string name = sel_getName(sel);
        std::map<std::string, ClassHookInfo *>::iterator iter = _hookInfoMap.find(name);
        if (iter == _hookInfoMap.end()) {
            return nullptr;
        }
        else
        {
            return iter->second;
        }
    }
    
    //void BaseHookLogic::setLogicMgr(HookLogicMgr *logicMgr)
    //{
    //    _logicMgr = logicMgr;
    //}
    //
    //HookLogicMgr *BaseHookLogic::getLogicMgr()
    //{
    //    return _logicMgr;
    //}
    
    //void BaseHookLogic::initMessageHook()
    //{
    //    
    //}
}
