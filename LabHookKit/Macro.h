//
//  Utils.h
//  LabHookKit
//
//  Created by lemon4ex on 2018/4/3.
//  Copyright © 2018年 lemon4ex. All rights reserved.
//

#ifndef Macro_h
#define Macro_h

//////////////// Hook ////////////////
#define DECLARE_HOOK_MESSAGE_MAP(_logic_class,_class) \
private: \
static const LabHookKit::HookModifyInfo _ ## _logic_class ## _msgInfo[]; \
public: \
virtual void initHook();\
virtual std::string getClassName(){ \
return #_class; \
}

#define DECLARE_HOOK_MESSAGE_MAP_V2(_class) \
DECLARE_HOOK_MESSAGE_MAP(_class##HookLogic,_class)

#define BEGIN_HOOK_MESSAGE_MAP(_logic_class) \
const LabHookKit::HookModifyInfo _logic_class::_ ## _logic_class ## _msgInfo[] =  \
{

#define BEGIN_HOOK_MESSAGE_MAP_V2(_class) \
BEGIN_HOOK_MESSAGE_MAP(_class##HookLogic)

#define END_HOOK_MESSAGE_MAP_V2(_class) \
END_HOOK_MESSAGE_MAP(_class##HookLogic)

#define END_HOOK_MESSAGE_MAP(_logic_class)\
};\
void _logic_class::initHook(){ \
for (size_t i = 0 ; i < sizeof(_logic_class::_ ## _logic_class ## _msgInfo)/sizeof(LabHookKit::HookModifyInfo); i++) {\
if(_ ## _logic_class ## _msgInfo[i].modifyType == 0)\
{\
if (_ ## _logic_class ## _msgInfo[i].isClassMethod) {\
hookClassMethod(_ ## _logic_class ## _msgInfo[i].methodName,_ ## _logic_class ## _msgInfo[i].methodIMP);\
}\
else \
{\
hookInstanceMethod(_ ## _logic_class ## _msgInfo[i].methodName,_ ## _logic_class ## _msgInfo[i].methodIMP);\
}\
}\
else\
{\
if (_ ## _logic_class ## _msgInfo[i].isClassMethod) {\
addClassMethod(_ ## _logic_class ## _msgInfo[i].methodName,_ ## _logic_class ## _msgInfo[i].methodIMP, _ ## _logic_class ## _msgInfo[i].typeEncoding);\
}\
else \
{\
addInstanceMethod(_ ## _logic_class ## _msgInfo[i].methodName,_ ## _logic_class ## _msgInfo[i].methodIMP, _ ## _logic_class ## _msgInfo[i].typeEncoding);\
}\
}\
}\
}

#define ADD_HOOK_INSTANCE_MESSAGE(_logic_class,_name,_func,_type) \
{false,#_name,#_type,(LabHookKit::HookMagicFuncPtr)&_logic_class::_func,1},

#define ADD_HOOK_INSTANCE_MESSAGE_V2(_class,_name,_func,_type) \
ADD_HOOK_INSTANCE_MESSAGE(_class##HookLogic,_name,_func,_type)

#define ADD_HOOK_CLASS_MESSAGE(_logic_class,_name,_func,_type) \
{true,#_name,#_type,(LabHookKit::HookMagicFuncPtr)&_logic_class::_func,1},

#define ADD_HOOK_CLASS_MESSAGE_V2(_class,_name,_func,_type) \
ADD_HOOK_CLASS_MESSAGE(_class##HookLogic,_name,_func,_type)

#define HOOK_INSTANCE_MESSAGE(_logic_class,_name,_func) \
{false,#_name,"",(LabHookKit::HookMagicFuncPtr)&_logic_class::_func,0},

#define HOOK_INSTANCE_MESSAGE_V2(_class,_name,_func) \
HOOK_INSTANCE_MESSAGE(_class##HookLogic,_name,_func)

#define HOOK_CLASS_MESSAGE(_logic_class,_name,_func) \
{true,#_name,"",(LabHookKit::HookMagicFuncPtr)&_logic_class::_func,0},

#define HOOK_CLASS_MESSAGE_V2(_class,_name,_func) \
HOOK_CLASS_MESSAGE(_class##HookLogic,_name,_func)

#define DECLARE_HOOK_MESSAGE(_ret_type,_func_name,...)\
_ret_type _func_name(SEL sel, ##__VA_ARGS__);

#define DECLARE_HOOK_MESSAGE_V2(_ret_type,_func_name,...) \
DECLARE_HOOK_MESSAGE(_ret_type,_func_name,...)

#define DEFINITION_HOOK_MESSAGE(_logic_class,_ret_type,_func_name,...)\
_ret_type _logic_class::_func_name(SEL sel, ##__VA_ARGS__)

#define DEFINITION_HOOK_MESSAGE_V2(_class,_ret_type,_func_name,...) \
DEFINITION_HOOK_MESSAGE(_class##HookLogic,_ret_type,_func_name,...)

//////////////// 实现 ////////////////
#define DECLARE_IMPLEMENT_MESSAGE_MAP(_logic_class,_super_class,_class) \
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

#define DECLARE_IMPLEMENT_MESSAGE_MAP_V2(_super_class,_class) \
DECLARE_IMPLEMENT_MESSAGE_MAP(_class##HookLogic,_super_class,_class)

#define BEGIN_IMPLEMENT_MESSAGE_MAP_V2(_class) \
BEGIN_IMPLEMENT_MESSAGE_MAP(_class##HookLogic)

#define BEGIN_IMPLEMENT_MESSAGE_MAP(_logic_class) \
const LabHookKit::ImplementInfo _logic_class::_ ## _logic_class ## _msgInfo[] =  \
{

#define END_IMPLEMENT_MESSAGE_MAP_V2(_class)\
END_IMPLEMENT_MESSAGE_MAP(_class##HookLogic)

#define END_IMPLEMENT_MESSAGE_MAP(_logic_class)\
};\
void _logic_class::initImplement(){ \
for (size_t i = 0 ; i < sizeof(_logic_class::_ ## _logic_class ## _msgInfo)/sizeof(LabHookKit::ImplementInfo); i++) {\
if (_ ## _logic_class ## _msgInfo[i].isClassMethod) {\
addClassMethod(_ ## _logic_class ## _msgInfo[i].methodName,_ ## _logic_class ## _msgInfo[i].methodIMP, _ ## _logic_class ## _msgInfo[i].typeEncoding);\
}\
else \
{\
addInstanceMethod(_ ## _logic_class ## _msgInfo[i].methodName,_ ## _logic_class ## _msgInfo[i].methodIMP, _ ## _logic_class ## _msgInfo[i].typeEncoding);\
}\
}\
}

#define ADD_IMPLEMENT_INSTANCE_MESSAGE(_logic_class,_name,_func,_type) \
{false,#_name,_type,(LabHookKit::IMPMagicFuncPtr)&_logic_class::_func},

#define ADD_IMPLEMENT_INSTANCE_MESSAGE_V2(_class,_name,_func,_type) \
ADD_IMPLEMENT_INSTANCE_MESSAGE(_class##HookLogic,_name,_func,_type)

#define ADD_IMPLEMENT_CLASS_MESSAGE(_logic_class,_name,_func,_type) \
{true,#_name,_type,(LabHookKit::IMPMagicFuncPtr)&_logic_class::_func},

#define ADD_IMPLEMENT_CLASS_MESSAGE_V2(_class,_name,_func,_type) \
ADD_IMPLEMENT_CLASS_MESSAGE(_class##HookLogic,_name,_func,_type)

#define DECLARE_IMPLEMENT_MESSAGE(_ret_type,_func,...)\
_ret_type _func(SEL sel, ##__VA_ARGS__);

#define DEFINITION_IMPLEMENT_MESSAGE(_logic_class,_ret_type,_func,...)\
_ret_type _logic_class::_func(SEL sel, ##__VA_ARGS__)

#define DEFINITION_IMPLEMENT_MESSAGE_V2(_class,_ret_type,_func,...)\
DEFINITION_IMPLEMENT_MESSAGE(_class##HookLogic,_ret_type,_func,...)

#endif /* Utils_h */
