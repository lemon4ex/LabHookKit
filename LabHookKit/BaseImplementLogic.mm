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
        _class = objc_allocateClassPair(objc_getClass(_superClass.c_str()), _className.c_str(), 0);
        objc_registerClassPair(_class);
    }
    
    bool BaseImplementLogic::addObjCMethod(const std::string &name, void *function, const std::string &types)
    {
        return class_addMethod(_class, sel_registerName(name.c_str()), (IMP)function, types.c_str());
    }
    
    BaseImplementLogic::~BaseImplementLogic()
    {
        
    }
    
    void BaseImplementLogic::initImplement()
    {
        
    }
    
    std::string BaseImplementLogic::getClassName()
    {
        return _className;
    }
}
