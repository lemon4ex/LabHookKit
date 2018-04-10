//
//  BaseImplementLogic.m
//  LabHookKit
//
//  Created by lemon4ex on 2018/3/12.
//  Copyright © 2018年 lemon4ex. All rights reserved.
//

#import "BaseImplementLogic.h"

namespace LabHookKit {
        
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
    
    Class BaseImplementLogic::getClass(){
        return _class;
    }
    
    BaseImplementLogic::~BaseImplementLogic()
    {
        
    }
        
    void BaseImplementLogic::allocateClass()
    {
        std::string className = getClassName();
        std::string superName = getSuperClassName();
        _class = objc_allocateClassPair(objc_getClass(superName.c_str()), className.c_str(), 0);
    }
    
    void BaseImplementLogic::registerClass()
    {
        objc_registerClassPair(_class);
    }
}
