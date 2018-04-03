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
        bool addObjCMethod(const std::string &name, IMPMagicFuncPtr imp, const std::string &types);
//        bool addInstanceVar(const std::string &name, const std::string &types);
        virtual ~BaseImplementLogic();
        
        ///< 给类增加方法、属性等都在此函数中实现
        virtual void initImplement();
    };
}

#define DECLARE_CLASS_BEGIN(super_name,class_name) \
@interface class_name : super_name

#define DECLARE_CLASS_END() \
@end;

#define IMPLEMENT_LOGIC_BEGIN(_super,_logic) \
class _logic : public _super {

#define IMPLEMENT_LOGIC_CONSTRUCTOR(super_logic_name,logic_name,class_super_name,class_name) \
public:\
logic_name():super_logic_name(#class_super_name,#class_name) \

#define IMPLEMENT_LOGIC_END() \
};

#define IMPLEMENT_LOGIC_MAGIC_METHOD(return_type,func_name, ...) \
return_type func_name(SEL sel, ##__VA_ARGS__)

#define IMPLEMENT_LOGIC_MAGIC_METHOD_MAP_BEGIN() \
virtual void initImplement() {

#define IMPLEMENT_LOGIC_MAGIC_METHOD_MAP_END() \
}

#define ON_IMPLEMENT_LOGIC_MAGIC_METHOD(method_name,func_name,types) \
addObjCMethod(#method_name, (LabHookKit::IMPMagicFuncPtr)&func_name, #types);

#endif

