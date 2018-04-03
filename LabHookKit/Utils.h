//
//  Utils.h
//  LabHookKit
//
//  Created by lemon4ex on 2018/4/3.
//  Copyright © 2018年 lemon4ex. All rights reserved.
//

#ifndef Utils_h
#define Utils_h

//////////////// Hook ////////////////

#define HOOK_LOGIC_BEGIN(super_name,logic_name) \
class logic_name : public super_name { \

#define HOOK_LOGIC_END() \
};

#define HOOK_LOGIC_CONSTRUCTOR(super_logic_name,logic_name,class_name) \
public:\
logic_name():super_logic_name(#class_name) \

#define HOOK_LOGIC_MAGIC_METHOD(return_type,func_name, ...) \
return_type func_name(SEL sel, ##__VA_ARGS__)

#define HOOK_LOGIC_MAGIC_METHOD_MAP_BEGIN() \
virtual void initHook() {

#define HOOK_LOGIC_MAGIC_METHOD_MAP_END() \
}

#define ON_HOOK_LOGIC_INSTANCE_METHOD(method_name,func_name) \
hookInstanceMethod(#method_name, (LabHookKit::HookMagicFuncPtr)&func_name);

#define ON_HOOK_LOGIC_CLASS_METHOD(method_name,func_name) \
hookClassMethod(#method_name, (LabHookKit::HookMagicFuncPtr)&func_name);



//////////////// 实现 ////////////////
#define DECLARE_CLASS_BEGIN(super_name,class_name) \
@interface class_name : super_name

#define DECLARE_CLASS_END() \
@end;

#define IMPLEMENT_LOGIC_BEGIN(super_name,logic_name) \
class logic_name : public super_name {

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

#endif /* Utils_h */
