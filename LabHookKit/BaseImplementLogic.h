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
    
    class BaseImplementLogic {
        std::string _className;
        std::string _superClass;
        Class _class;
    public:
        BaseImplementLogic(const std::string &superClass, const std::string &className);
        std::string getClassName();
        bool addObjCMethod(const std::string &name, void *function, const std::string &types);
        virtual ~BaseImplementLogic();
        virtual void initImplement();
    };
}
#endif

