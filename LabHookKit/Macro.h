//
//  Utils.h
//  LabHookKit
//
//  Created by lemon4ex on 2018/4/3.
//  Copyright © 2018年 lemon4ex. All rights reserved.
//

#ifndef Macro_h
#define Macro_h

// 定义self变量
#define DECLARE_SELF(_class) \
_class *self = (__bridge _class *)this;

// 定义self变量，只是为了宏与V2版本匹配
#define DECLARE_SELF_V2(_class) \
DECLARE_SELF(_class)

// 声明oc类，以便使用类指针
#define DECLARE_CLASS(_class) \
@class _class;

// 声明Hook前的原OC方法
#define DECLARE_ORIGIN_MESSAGE(_logic_class, _class, _ret_type, _sel, ...)\
_ret_type (*_class##_originFuncPtr)(id, SEL, ##__VA_ARGS__) = ({\
DECLARE_SELF(_class)\
_logic_class *logic = dynamic_cast<_logic_class *>(LabHookKit::HookLogicMgr::sharedMgr()->getHookLogic(self));\
LabHookKit::ClassHookInfo *info = logic->getClassHookInfo(_sel);\
(_ret_type (*)(id, SEL, ##__VA_ARGS__))info->originImp;\
})

#define DECLARE_ORIGIN_MESSAGE_V2(_class, _ret_type, ...)\
DECLARE_ORIGIN_MESSAGE(_class##HookLogic, _class, _ret_type, sel, ##__VA_ARGS__)

// 调用Hook前的原OC方法
#define ORIGIN_MESSAGE(_logic_class, _class, _ret_type, _sel, ...)\
_class##_originFuncPtr(self, _sel, ##__VA_ARGS__);

#define ORIGIN_MESSAGE_V2(_class, _ret_type, ...)\
ORIGIN_MESSAGE(_class##HookLogic, _class, _ret_type, sel, ##__VA_ARGS__)

// 定义父类(super)的OC方法
#define DECLARE_SUPER_MESSAGE(_class, _ret_type, _sel, ...)\
_ret_type (*_class##_super)(struct objc_super *, SEL, ##__VA_ARGS__) = (_ret_type (*)(struct objc_super *, SEL, ##__VA_ARGS__))objc_msgSendSuper;

#define DECLARE_SUPER_MESSAGE_V2(_class, _ret_type, ...)\
DECLARE_SUPER_MESSAGE(_class, _ret_type, sel, ##__VA_ARGS__)

// 调用父类(super)的OC方法
#define SUPER_MESSAGE(_class, _ret_type, _sel, ...)\
({\
DECLARE_SELF(_class)\
struct objc_super superClass = {self, self.superclass};\
_class##_super(&superClass, _sel, ##__VA_ARGS__);\
})

#define SUPER_MESSAGE_V2(_class, _ret_type, ...)\
SUPER_MESSAGE(_class, _ret_type, sel, ##__VA_ARGS__)

//////////////// Hook v1 ////////////////
// 声明一个Hook消息映射，帮助生成核心的函数和类变量
#define DECLARE_HOOK_MESSAGE_MAP(_logic_class, _class) \
private: \
static const LabHookKit::HookModifyInfo _ ## _logic_class ## _msgInfo[]; \
public: \
virtual void initHook();\
virtual std::string getClassName(){ \
return #_class; \
}

// 开始Hook消息映射
#define BEGIN_HOOK_MESSAGE_MAP(_logic_class) \
const LabHookKit::HookModifyInfo _logic_class::_ ## _logic_class ## _msgInfo[] =  \
{

// 结束Hook消息映射
#define END_HOOK_MESSAGE_MAP(_logic_class)\
};\
void _logic_class::initHook(){ \
for (size_t i = 0 ; i < sizeof(_logic_class::_ ## _logic_class ## _msgInfo)/sizeof(LabHookKit::HookModifyInfo); i++) {\
if(_ ## _logic_class ## _msgInfo[i].modifyType == 0)\
{\
if (_ ## _logic_class ## _msgInfo[i].isClassMethod) {\
hookClassMethod(_ ## _logic_class ## _msgInfo[i].methodName, _ ## _logic_class ## _msgInfo[i].methodIMP);\
}\
else \
{\
hookInstanceMethod(_ ## _logic_class ## _msgInfo[i].methodName, _ ## _logic_class ## _msgInfo[i].methodIMP);\
}\
}\
else\
{\
if (_ ## _logic_class ## _msgInfo[i].isClassMethod) {\
addClassMethod(_ ## _logic_class ## _msgInfo[i].methodName, _ ## _logic_class ## _msgInfo[i].methodIMP, _ ## _logic_class ## _msgInfo[i].typeEncoding);\
}\
else \
{\
addInstanceMethod(_ ## _logic_class ## _msgInfo[i].methodName, _ ## _logic_class ## _msgInfo[i].methodIMP, _ ## _logic_class ## _msgInfo[i].typeEncoding);\
}\
}\
}\
}

// 添加新实例方法
#define ADD_HOOK_INSTANCE_MESSAGE(_logic_class, _name, _func, _type) \
{false, #_name, #_type, (LabHookKit::HookMagicFuncPtr)&_logic_class::_func, 1}, 

// 添加新类方法
#define ADD_HOOK_CLASS_MESSAGE(_logic_class, _name, _func, _type) \
{true, #_name, #_type, (LabHookKit::HookMagicFuncPtr)&_logic_class::_func, 1}, 

// Hook实例方法
#define HOOK_INSTANCE_MESSAGE(_logic_class, _name, _func) \
{false, #_name, "", (LabHookKit::HookMagicFuncPtr)&_logic_class::_func, 0}, 

// Hook类方法
#define HOOK_CLASS_MESSAGE(_logic_class, _name, _func) \
{true, #_name, "", (LabHookKit::HookMagicFuncPtr)&_logic_class::_func, 0}, 

// 声明一个新的方法实现
#define DECLARE_HOOK_MESSAGE(_ret_type, _func_name, ...)\
_ret_type _func_name(SEL sel, ##__VA_ARGS__);

// 定义一个新的方法实现
#define DEFINITION_HOOK_MESSAGE(_logic_class, _ret_type, _func_name, ...)\
_ret_type _logic_class::_func_name(SEL sel, ##__VA_ARGS__)

//////////////// Hook v2 ////////////////
#define DECLARE_HOOK_MESSAGE_MAP_V2(_class) \
DECLARE_HOOK_MESSAGE_MAP(_class##HookLogic, _class)

#define BEGIN_HOOK_MESSAGE_MAP_V2(_class) \
BEGIN_HOOK_MESSAGE_MAP(_class##HookLogic)

#define END_HOOK_MESSAGE_MAP_V2(_class) \
END_HOOK_MESSAGE_MAP(_class##HookLogic)

#define ADD_HOOK_INSTANCE_MESSAGE_V2(_class, _name, _func, _type) \
ADD_HOOK_INSTANCE_MESSAGE(_class##HookLogic, _name, _func, _type)

#define ADD_HOOK_CLASS_MESSAGE_V2(_class, _name, _func, _type) \
ADD_HOOK_CLASS_MESSAGE(_class##HookLogic, _name, _func, _type)

#define HOOK_INSTANCE_MESSAGE_V2(_class, _name, _func) \
HOOK_INSTANCE_MESSAGE(_class##HookLogic, _name, _func)

#define HOOK_CLASS_MESSAGE_V2(_class, _name, _func) \
HOOK_CLASS_MESSAGE(_class##HookLogic, _name, _func)

#define DECLARE_HOOK_MESSAGE_V2(_ret_type, _func_name, ...) \
DECLARE_HOOK_MESSAGE(_ret_type, _func_name, ##__VA_ARGS__)

#define DEFINITION_HOOK_MESSAGE_V2(_class, _ret_type, _func_name, ...) \
DEFINITION_HOOK_MESSAGE(_class##HookLogic, _ret_type, _func_name, ##__VA_ARGS__)

//////////////// 实现 v1 ////////////////
// 声明一个实现新类的消息映射，帮助生成核心的函数和类变量
#define DECLARE_IMPLEMENT_MESSAGE_MAP(_logic_class, _super_class, _class) \
private: \
static const LabHookKit::ImplementInfo _ ## _logic_class ## _msgInfo[]; \
public: \
virtual void initImplement();\
virtual std::string getClassName(){ \
return #_class; \
} \
\
virtual std::string getSuperClassName(){ \
return #_super_class; \
}\

// 开始实现新的消息映射
#define BEGIN_IMPLEMENT_MESSAGE_MAP(_logic_class) \
const LabHookKit::ImplementInfo _logic_class::_ ## _logic_class ## _msgInfo[] =  \
{

// 结束实现新的消息映射
#define END_IMPLEMENT_MESSAGE_MAP(_logic_class)\
};\
void _logic_class::initImplement(){ \
for (size_t i = 0 ; i < sizeof(_logic_class::_ ## _logic_class ## _msgInfo)/sizeof(LabHookKit::ImplementInfo); i++) {\
if (_ ## _logic_class ## _msgInfo[i].isClassMethod) {\
addClassMethod(_ ## _logic_class ## _msgInfo[i].methodName, _ ## _logic_class ## _msgInfo[i].methodIMP, _ ## _logic_class ## _msgInfo[i].typeEncoding);\
}\
else \
{\
addInstanceMethod(_ ## _logic_class ## _msgInfo[i].methodName, _ ## _logic_class ## _msgInfo[i].methodIMP, _ ## _logic_class ## _msgInfo[i].typeEncoding);\
}\
}\
}

// 添加新实例方法
#define ADD_IMPLEMENT_INSTANCE_MESSAGE(_logic_class, _name, _func, _type) \
{false, #_name, _type, (LabHookKit::IMPMagicFuncPtr)&_logic_class::_func}, 

// 添加新类方法
#define ADD_IMPLEMENT_CLASS_MESSAGE(_logic_class, _name, _func, _type) \
{true, #_name, _type, (LabHookKit::IMPMagicFuncPtr)&_logic_class::_func}, 

// 声明一个新类的方法
#define DECLARE_IMPLEMENT_MESSAGE(_ret_type, _func, ...)\
_ret_type _func(SEL sel, ##__VA_ARGS__);

// 定义一个新类的方法
#define DEFINITION_IMPLEMENT_MESSAGE(_logic_class, _ret_type, _func, ...)\
_ret_type _logic_class::_func(SEL sel, ##__VA_ARGS__)

//////////////// 实现 v2 ////////////////
#define DECLARE_IMPLEMENT_MESSAGE_MAP_V2(_super_class, _class) \
DECLARE_IMPLEMENT_MESSAGE_MAP(_class##Logic, _super_class, _class)

#define BEGIN_IMPLEMENT_MESSAGE_MAP_V2(_class) \
BEGIN_IMPLEMENT_MESSAGE_MAP(_class##Logic)

#define END_IMPLEMENT_MESSAGE_MAP_V2(_class)\
END_IMPLEMENT_MESSAGE_MAP(_class##Logic)

#define ADD_IMPLEMENT_INSTANCE_MESSAGE_V2(_class, _name, _func, _type) \
ADD_IMPLEMENT_INSTANCE_MESSAGE(_class##Logic, _name, _func, _type)

#define ADD_IMPLEMENT_CLASS_MESSAGE_V2(_class, _name, _func, _type) \
ADD_IMPLEMENT_CLASS_MESSAGE(_class##Logic, _name, _func, _type)

#define DEFINITION_IMPLEMENT_MESSAGE_V2(_class, _ret_type, _func, ...)\
DEFINITION_IMPLEMENT_MESSAGE(_class##Logic, _ret_type, _func, ##__VA_ARGS__)

#endif /* Utils_h */
