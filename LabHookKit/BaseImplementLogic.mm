//
//  BaseImplementLogic.m
//  LabHookKit
//
//  Created by lemon4ex on 2018/3/12.
//  Copyright © 2018年 lemon4ex. All rights reserved.
//

#import "BaseImplementLogic.h"

namespace LabHookKit {
    
    BaseImplementLogic::BaseImplementLogic(const std::string &superClass, const std::string &className):
    _superClass(superClass),
    _className(className)
    {
        
    }
    
    bool BaseImplementLogic::addInstanceMethod(const std::string &name, IMPMagicFuncPtr imp, const std::string &types)
    {
        return addObjCMethod(_class, name, imp, types);
    }
    
    bool BaseImplementLogic::addClassMethod(const std::string &name, IMPMagicFuncPtr imp, const std::string &types)
    {
        Class _mate_class = object_getClass(_class);
        return addObjCMethod(_mate_class, name, imp, types);
    }
    
    bool BaseImplementLogic::addObjCMethod(Class _class,const std::string &name, IMPMagicFuncPtr imp, const std::string &types)
    {
        void *function = &imp;
        return class_addMethod(_class, sel_registerName(name.c_str()), (IMP)(*(size_t *)function), types.c_str());
    }
    
    BaseImplementLogic::~BaseImplementLogic()
    {
        
    }
    
//    void BaseImplementLogic::initImplement()
//    {
//        
//    }
    
    void BaseImplementLogic::allocateClass()
    {
        _class = objc_allocateClassPair(objc_getClass(_superClass.c_str()), _className.c_str(), 0);
    }
    
    void BaseImplementLogic::registerClass()
    {
        objc_registerClassPair(_class);
    }
    
    std::string BaseImplementLogic::getClassName()
    {
        return _className;
    }
}
